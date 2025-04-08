#ifndef PLAYER
#define PLAYER

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"


typedef struct Player{
    Vector2 posicao;
    int vida;
    int index_cursor;
    float vel;
}Player;

#include "string_func.h"

Player CreatePlayer(int screenWidth, int screenHeight);
void UpdatePlayer(Player *player, Rectangle *textbox, StringActions *head, float dt);
void DrawPlayer(Player player);
void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, Rectangle *textbox, float delta, int width, int height);

#include "player.c"
#endif