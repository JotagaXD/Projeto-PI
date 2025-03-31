#ifndef PLAYER
#define PLAYER

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"

typedef struct {
    Vector2 posicao;
    float vel;
}Player;

void UpdatePlayer(Player *player, float dt);
void DrawPlayer(Player player);
void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, Rectangle *textbox, float delta, int width, int height);

#include "player.c"
#endif