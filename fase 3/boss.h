#ifndef BOSS
#define BOSS

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int vida;
    int velocidade_ataque;
    int ataque;
    int cooldown_atk;
} Boss;

void initBoss(Boss *boss, int vida, int velocidade_ataque, int ataque, int cooldown_atk);
void drawBoss(Boss *boss, int x, int y);
void updateBossAttack(Boss *boss, Rectangle *area_tiro);
void updateBoss(Boss *boss, int dano, Rectangle area_boss, Rectangle *area_tiro, Rectangle area_ataque_inimigo, int *cooldown_atk);

#include "boss.c"
#endif