#include "string_func.h"

StringActions* createStringActions(char* string) {
    StringActions* newStringActions = (StringActions*)malloc(sizeof(StringActions));
    if(newStringActions==NULL) {
        printf("Problema no createStringActions\n"); exit(1);
    }
    newStringActions->string = strdup(string);
    newStringActions->next = NULL;
    return newStringActions;
}

StringActions* insertAtBeginning(StringActions* head, char* string) {
    StringActions* newStringActions = createStringActions(string);
    newStringActions->next = head;
    return newStringActions;
}

StringActions* insertAtEnd(StringActions* head, char* string, int* Num_ammo) {
    StringActions* newStringActions = createStringActions(string);
    if ((*Num_ammo) < 5)(*Num_ammo)++;
    if (head == NULL) {
        return newStringActions;
    }
    StringActions* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStringActions;
    return head;
}

StringActions* deleteStringActions(StringActions* head, int* Num_ammo) {
    if ((*Num_ammo) > 0) { 
        (*Num_ammo)--;
        StringActions* temp = head;
        head = head->next;
        free(temp);
    }
    return head;
}

void UpdateTextbox(StringActions *head, char *action_string, int *letterCount, int Num_ammo)
{
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (*letterCount < MAX_INPUT_CHARS))
        {
            action_string[(*letterCount)] = (char)key;
            action_string[(*letterCount)+1] = '\0'; // Add null terminator at the end of the string.
            (*letterCount)++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE))
    {
        (*letterCount)--;
        if ((*letterCount) < 0) (*letterCount) = 0;
        action_string[(*letterCount)] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (strcmp(action_string, head->string) == 0) {
            (*letterCount) = 0;
            action_string[(*letterCount)] = '\0';
            //head = deleteStringActions(head, &Num_ammo);
        }
    }
}

void DrawList(StringActions* head, int size, EnvItem* envItems) {
    StringActions* temp = head;
    for (int j = 0; j < size; j++) {
        DrawText(temp->string, (int)envItems[j].rect.x + 2, (int)envItems[j].rect.y + 6, 20, GREEN);
        temp = temp->next;
    }
}