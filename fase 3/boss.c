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
    int tempo_ataque;
} Boss;

void initBoss(Boss *boss, int vida, int velocidade_ataque, int ataque, int tempo_ataque) // Inicializar Boss(Chamar função apenas 1 vez)
{
    boss->vida = vida;
    boss->velocidade_ataque = velocidade_ataque;
    boss->ataque = ataque;
    boss->tempo_ataque = tempo_ataque;
}

void drawBoss(Boss *boss, int x, int y) // Desenhar boss
{
    if (boss->vida <= 0)
    {
        DrawText("BOSS DERROTADO", x, y - 20, 20, RED);
        return;
    }
    DrawRectangle(x, y, 50, 50, RED);
    DrawText(TextFormat("Vida: %d", boss->vida), x, y - 20, 10, WHITE);
    DrawText(TextFormat("Ataque: %d", boss->ataque), x, y - 10, 10, WHITE);
}

void updateBossAttack(Boss *boss, Rectangle *area_tiro)
{
    // Move o tiro para a esquerda
    area_tiro->x -= boss->velocidade_ataque;

    // Desenha o novo tiro
    DrawRectangle(area_tiro->x, area_tiro->y, area_tiro->width, area_tiro->height, BLUE);
}

void updateBoss(Boss *boss, int dano, Rectangle area_boss, Rectangle *area_tiro, Rectangle area_ataque_inimigo, int *tempo_ataque) // Atualizar boss
{
    drawBoss(boss, area_boss.x, area_boss.y);

    if (CheckCollisionRecs(area_boss, area_ataque_inimigo)) // Checa se o Boss foi atingidp
    {
        boss->vida -= dano;
        if (boss->vida < 0)
            boss->vida = 0;
    }

    if (*tempo_ataque == boss->tempo_ataque) // Verifica se o tempo de ataque do boss chegou
    {
        // Atira
        area_tiro->x = area_boss.x;
        area_tiro->y = area_boss.y + area_boss.height / 2 - area_tiro->height / 2;
        *tempo_ataque = 0;
    }
    else
    {
        // Espera
        (*tempo_ataque)++;
    }

    // Atualiza posição do tiro se estiver ativo
    if (area_tiro->x + area_tiro->width > 0)
    {
        updateBossAttack(boss, area_tiro);
    }
}