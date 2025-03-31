#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"


#define MAX_INPUT_CHARS    25
#define PLAYER_H_SPEED 5

typedef struct {
    Vector2 posicao;
    float vel;
}Player;

typedef struct {
    int vida;
    float vel;
}Boss;

typedef struct {
    Rectangle rect;
    Color color;
}EnvItem;

typedef struct StringActions{
    char* string;
    struct StringActions* next;
}StringActions;

void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, Rectangle *textbox, float delta, int width, int height);
void UpdatePlayer(Player *player, float dt, Rectangle *textbox);
void UpdateTextbox(Player *player, Rectangle * textbox);

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
    if ((*Num_ammo) > 0) (*Num_ammo)--;
    StringActions* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void DrawList(StringActions* head, int size, EnvItem* envItems) {
    StringActions* temp = head;
    for (int j = 0; j < size; j++) {
        DrawText(temp->string, (int)envItems[j].rect.x + 2, (int)envItems[j].rect.y + 6, 20, GREEN);
        temp = temp->next;
    }
}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

int main () {
    const int screenWidth = 800, screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Test");
    
    Player player;
    player.posicao.x = 0;
    player.posicao.y = 0;
    player.vel = 0;

    char action_string[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textbox;
    textbox.width = 550; textbox.height = 30;
    bool textboxselect = true;
    
    EnvItem envItems[] = {
        {{25, 400, 150, 30}, GRAY},
        {{175, 400, 150, 30}, GRAY},
        {{325, 400, 150, 30}, GRAY},
        {{475, 400, 150, 30}, GRAY},
        {{625, 400, 150, 30}, GRAY}
    };

    StringActions* head = NULL;
    int Num_ammo = 0;

    
    
    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);
    
    Rectangle boss_text;//trabalhar isso igual envitems
    boss_text.x = 200; boss_text.y = 200;
    boss_text.width = 100; boss_text.height = 30;
    char ataques_boss[5][25] = {"banana", "paralelepipedo", "latrel", "intankavel", "tenhamisericordia"};
    
    for (int i = 0; i < 5; i ++){
        head = insertAtEnd(head, ataques_boss[i], &Num_ammo);
    }

    Camera2D camera = { 0 };
    camera.target = player.posicao;
    camera.offset.x = screenWidth/2.0f; camera.offset.y = screenHeight/2.0f;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int framesCounter = 0;
    int lastDelete;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int time = GetTime(); //fazer com base na frame rate e nao no tempo

        ClearBackground(WHITE);
        
        if (textboxselect)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    action_string[letterCount] = (char)key;
                    action_string[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                action_string[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (strcmp(action_string, head->string) == 0) {
                    letterCount = 0;
                    action_string[letterCount] = '\0';
                    head = deleteStringActions(head, &Num_ammo);
                }
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (textboxselect) framesCounter++;
        else framesCounter = 0;

        UpdatePlayer(&player, dt, &textbox);
        UpdateCameraPlayerBoundsPush(&camera, &player, &textbox, dt, screenWidth, screenHeight);

        BeginDrawing();
            BeginMode2D(camera);
                Rectangle playerRect = { player.posicao.x - 20, player.posicao.y - 40, 40.0f, 40.0f };

                DrawRectangleRec(playerRect, RED);

                //DrawRectangleRec(textbox, LIGHTGRAY);
                //if (textboxselect) DrawRectangleLines((int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height, RED);
                //else DrawRectangleLines((int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height, DARKGRAY);

                DrawText(head->string, (int)textbox.x + 1, (int)textbox.y + 3, 30, LIGHTGRAY);

                DrawText(action_string, (int)textbox.x + 1, (int)textbox.y + 3, 30, MAROON);

                //DrawText(TextFormat("WRITE YOUR ACTION: %i/%i", letterCount, MAX_INPUT_CHARS), 255, 350, 20, DARKGRAY);

            EndMode2D();

            for (int i = 0; i < envItemsLength; i++) { 
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleLines((int)envItems[i].rect.x, (int)envItems[i].rect.y, (int)envItems[i].rect.width, (int)envItems[i].rect.height, DARKGRAY);
                DrawList(head, Num_ammo, envItems);
            }

        EndDrawing();
        //if (time % 3 == 0 && time != lastDelete && head != NULL) {
        //    head = deleteStringActions(head, &Num_ammo);
        //    lastDelete = time; // Update the last deletion time
        //}
    }

    CloseWindow(); 

    return 0;
}

void UpdatePlayer(Player *player, float dt, Rectangle *textbox) {
    //Vector2 movimento = {0};
    if (IsKeyDown(KEY_RIGHT)) player->posicao.x += 300*dt;
    if (IsKeyDown(KEY_LEFT)) player->posicao.x -= 300*dt;
    if (IsKeyDown(KEY_DOWN)) player->posicao.y += 300*dt;
    if (IsKeyDown(KEY_UP)) player->posicao.y -= 300*dt;
    //if ((IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) || (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))) {}
    
}   

void UpdateTextbox(Player *player, Rectangle *textbox){
    
}


void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, Rectangle *textbox, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->posicao.x < bboxWorldMin.x) camera->target.x = player->posicao.x; textbox->x = player->posicao.x;
    if (player->posicao.y < bboxWorldMin.y) camera->target.y = player->posicao.y; textbox->y = player->posicao.y;
    if (player->posicao.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x); textbox->x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x);
    if (player->posicao.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y); textbox->y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y);
}