#ifndef STRING
#define STRING

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include "player.h"

#define MAX_INPUT_CHARS    25

typedef struct StringActions{
    char* string;
    struct StringActions* next;
}StringActions;

typedef struct {
    Rectangle rect;
    Color color;
}EnvItem;

StringActions* createStringActions(char* string);
StringActions* insertAtBeginning(StringActions* head, char* string);
StringActions* insertAtEnd(StringActions* head, char* string, int* Num_ammo);
StringActions* deleteStringActions(StringActions* head, int* Num_ammo);
void UpdateTextbox(StringActions **head, char *action_string, Player *player, int *Num_ammo);
void DrawList(StringActions* head, int size, EnvItem* envItems); 

#include "string_func.c"
#endif