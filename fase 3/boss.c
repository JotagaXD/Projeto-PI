#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boss.h"

void initBoss(Boss *boss, int vida, int velocidade_ataque, int ataque, int cooldown_atk)
{
    boss->vida = vida;
    boss->velocidade_ataque = velocidade_ataque;
    boss->ataque = ataque;
    boss->cooldown_atk = cooldown_atk;
    boss->angulo_espiral = 0;
    boss->padrao_atual = 0;
}

void drawBoss(Boss *boss, int x, int y)
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

void gerarPadraoAtaque(Boss *boss, Projetil projeteis[], int padrao)
{

    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        projeteis[i].ativo = false;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    switch (padrao)
    {
    case 0: // PADRÃO 1: Chuva
    {
        for (int i = 0; i < 15; i++)
        {
            projeteis[i].ativo = true;
            projeteis[i].area = (Rectangle){
                GetRandomValue(50, screenWidth - 50),
                0,
                15, 15};
            projeteis[i].velocidade = (Vector2){
                GetRandomValue(-1, 1), // Pequena variação horizontal
                GetRandomValue(3, 6)   // Velocidade vertical variável
            };
            projeteis[i].angulo = 0;
        }
        break;
    }

    case 1: // PADRÃO 2: Espiral
    {
        float anguloBase = boss->angulo_espiral;
        for (int i = 0; i < 25; i++)
        {
            float angulo = anguloBase + i * (2 * PI / 12);

            projeteis[i].ativo = true;
            projeteis[i].area = (Rectangle){
                screenWidth / 2,
                10,
                12, 12};

            // Velocidade baseada no ângulo para criar efeito espiral
            projeteis[i].velocidade = (Vector2){
                4 * cosf(angulo),
                4 * sinf(angulo)};
            projeteis[i].angulo = angulo;
        }

        boss->angulo_espiral += 0.2f;
        if (boss->angulo_espiral > 2 * PI)
            boss->angulo_espiral -= 2 * PI;
        break;
    }

    case 2: // PADRÃO 3: convergente
    {
        // Projéteis que convergem de todos os lados para o centro e depois divergem
        for (int i = 0; i < 35; i++)
        {
            projeteis[i].ativo = true;

            int lado = GetRandomValue(0, 3); // 0: topo, 1: direita, 2: baixo, 3: esquerda

            switch (lado)
            {
            case 0:
                projeteis[i].area = (Rectangle){GetRandomValue(0, screenWidth), 0, 10, 10};
                break;
            case 1:
                projeteis[i].area = (Rectangle){screenWidth, GetRandomValue(0, screenHeight), 10, 10};
                break;
            case 2:
                projeteis[i].area = (Rectangle){GetRandomValue(0, screenWidth), screenHeight, 10, 10};
                break;
            case 3:
                projeteis[i].area = (Rectangle){0, GetRandomValue(0, screenHeight), 10, 10};
                break;
            }

            // Direção inicial ao centro da tela
            float targetX = screenWidth / 2;
            float targetY = screenHeight / 2;

            float dx = targetX - projeteis[i].area.x;
            float dy = targetY - projeteis[i].area.y;
            float dist = sqrtf(dx * dx + dy * dy);

            // Normalizar e dar velocidade
            float velocidade = GetRandomValue(3, 7);
            projeteis[i].velocidade = (Vector2){
                (dx / dist) * velocidade,
                (dy / dist) * velocidade};

            // Ângulo para rotação do projétil
            projeteis[i].angulo = atan2f(dy, dx);
        }
        break;
    }
    }
}

void atualizarProjeteis(Boss *boss, Projetil projeteis[])
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (!projeteis[i].ativo)
            continue;

        projeteis[i].area.x += projeteis[i].velocidade.x;
        projeteis[i].area.y += projeteis[i].velocidade.y;

        switch (boss->padrao_atual)
        {
        case 0: // Padrão Chuva
            break;

        case 1: // Padrão Espiral
            projeteis[i].velocidade.x *= 1.01f;
            projeteis[i].velocidade.y *= 1.01f;
            break;

        case 2: // Padrão convergente
            float centerX = screenWidth / 2;
            float centerY = screenHeight / 2;
            float dCentroX = centerX - projeteis[i].area.x;
            float dCentroY = centerY - projeteis[i].area.y;
            float distCentro = sqrtf(dCentroX * dCentroX + dCentroY * dCentroY);

            if (distCentro < 25)
            {
                // Inverte a direção para ir para fora
                projeteis[i].velocidade.x = -projeteis[i].velocidade.x * 1.5f;
                projeteis[i].velocidade.y = -projeteis[i].velocidade.y * 1.5f;
            }
            break;
        }

        // Desenha o tiro
        Color corProjetil;
        switch (boss->padrao_atual)
        {
        case 0:
            corProjetil = BLUE;
            break;
        case 1:
            corProjetil = PURPLE;
            break;
        case 2:
            corProjetil = RED;
            break;
        }

        projeteis[i].angulo += 0.1f;

        // Desenha o tiro
        DrawRectanglePro(projeteis[i].area, (Vector2){projeteis[i].area.width / 2, projeteis[i].area.height / 2}, projeteis[i].angulo * RAD2DEG, corProjetil);

        // Verifica se saiu da tela
        if (projeteis[i].area.x < -50 || projeteis[i].area.x > screenWidth + 50 ||
            projeteis[i].area.y < -50 || projeteis[i].area.y > screenHeight + 50)
        {
            projeteis[i].ativo = false;
        }
    }
}

void updateBoss(Boss *boss, int dano, Rectangle area_boss, Projetil projeteis[], Rectangle area_ataque_inimigo, int *cooldown_atk, int acertou_palavra, int dano_ataque)
{
    // Atualiza o padrão baseado na vida atual do boss
    int padrao_anterior = boss->padrao_atual;

    if (boss->vida > 70)
        boss->padrao_atual = 0;
    else if (boss->vida > 40)
        boss->padrao_atual = 1;
    else
        boss->padrao_atual = 2;

    drawBoss(boss, area_boss.x, area_boss.y);

    // Verificar se acertou a palavra
    if (acertou_palavra == 1)
    {
        boss->vida -= dano_ataque;
        if (boss->vida < 0)
            boss->vida = 0;
    }

    if (*cooldown_atk >= boss->cooldown_atk)
    {
        gerarPadraoAtaque(boss, projeteis, boss->padrao_atual);
        *cooldown_atk = 0;
    }
    else
    {
        (*cooldown_atk)++;
    }

    atualizarProjeteis(boss, projeteis);
}