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
    float angulo_espiral;
    int padrao_atual;
} Boss;

typedef struct
{
    Rectangle area;
    Vector2 velocidade;
    bool ativo;
    float angulo;
} Projetil;

#define MAX_PROJETEIS 100

void initBoss(Boss *boss, int vida, int velocidade_ataque, int ataque, int cooldown_atk);
void drawBoss(Boss *boss, int x, int y);
void gerarPadraoAtaque(Boss *boss, Projetil projeteis[], int padrao);
void atualizarProjeteis(Boss *boss, Projetil projeteis[]);
void updateBoss(Boss *boss, int dano, Rectangle area_boss, Projetil projeteis[], int *cooldown_atk, int *acertou_palavra, int dano_ataque);

#include "boss.c"
#endif