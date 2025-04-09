#ifndef PLAYER
#define PLAYER

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"


typedef struct Player{
    Rectangle posicao;
    int vida;
    int index_cursor;
    float vel;
}Player;

#include "boss.h"
#include "string_func.h"

Player CreatePlayer(int screenWidth, int screenHeight);
void UpdatePlayer(Player *player, Rectangle *textbox, StringActions *head, float dt);
void DrawPlayer(Player player);
void DamagePlayer(Player *player, Projetil *projeteis, int *invincibility);
void TempStringUpdt(Color *temp_yellow, Rectangle *temp_string_rect, bool *yellow_done);

#include "player.c"
#endif