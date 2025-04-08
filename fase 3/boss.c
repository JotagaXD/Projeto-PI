#include "boss.h"

void initBoss(Boss *boss, int vida, int velocidade_ataque, int ataque, int cooldown_atk) // Inicializar Boss(Chamar função apenas 1 vez)
{
    boss->vida = vida;
    boss->velocidade_ataque = velocidade_ataque;
    boss->ataque = ataque;
    boss->cooldown_atk = cooldown_atk;
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

void updateBossAttack(Boss *boss, Rectangle *tiros, int quantidade_tiros)
{
    for (int i = 0; i < quantidade_tiros; i++)
    {
        // Move o tiro para baixo
        tiros[i].y += boss->velocidade_ataque;

        // Desenha o tiro
        if (tiros[i].y > 0 && tiros[i].y < GetScreenHeight())
        {
            DrawRectangle(tiros[i].x, tiros[i].y, tiros[i].width, tiros[i].height, BLUE);
        }
    }
}

void updateBoss(Boss *boss, int dano, Rectangle area_boss, Rectangle *tiros, Rectangle area_ataque_inimigo, int *cooldown_atk, int acertou_palavra, int dano_ataque) // Atualizar boss
{
    drawBoss(boss, area_boss.x, area_boss.y);

    // Verificar se acertou a palavra
    if (acertou_palavra == 1)
    {
        boss->vida -= dano_ataque;
        if (boss->vida < 0)
            boss->vida = 0;
    }

    // Verifica colisão com o ataque do inimigo
    if (CheckCollisionRecs(area_boss, area_ataque_inimigo)) // Checa se o Boss foi atingido
    {
        boss->vida -= dano;
        if (boss->vida < 0)
            boss->vida = 0;
    }

    // Determina quantidade de tiros com base na vida do boss
    int quantidade_tiros = 0;
    if (boss->vida > 70 && boss->vida <= 100)
    {
        quantidade_tiros = 15;
    }
    else if (boss->vida > 40 && boss->vida <= 70)
    {
        quantidade_tiros = 25;
    }
    else if (boss->vida > 0 && boss->vida <= 40)
    {
        quantidade_tiros = 35;
    }

    if (*cooldown_atk == boss->cooldown_atk) // Verifica se o tempo de ataque do boss chegou
    {
        // Gera tiros aleatórios a partir do topo da tela
        for (int i = 0; i < quantidade_tiros; i++)
        {
            tiros[i].x = GetRandomValue(0, GetScreenWidth() - tiros[i].width);
            tiros[i].y = 0;
        }
        *cooldown_atk = 0;
    }
    else
    {
        (*cooldown_atk)++;
    }

    updateBossAttack(boss, tiros, quantidade_tiros);
}