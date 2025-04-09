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
        DrawText("BOSS DERROTADO", x - 30, y - 20, 20, RED);
        return;
    }
    DrawRectangle(x, y, 60, 60, BROWN);
    DrawText(TextFormat("BOSS HP: %d/200", boss->vida), x - 300, 10, 40, BLACK);
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
        for (int i = 0; i < 25; i++)
        {
            projeteis[i].ativo = true;
            projeteis[i].area = (Rectangle){GetRandomValue(50, screenWidth - 50),10, 15, 15};
            projeteis[i].velocidade = (Vector2){
                GetRandomValue(-1, 1), // Pequena variação horizontal
                GetRandomValue(6, 10)   // Velocidade vertical variável
            };
            projeteis[i].angulo = 0;
        }
        break;
    }

    case 1: // PADRÃO 2: Espiral
    {
        float anguloBase = boss->angulo_espiral;

        int atack_patern = GetRandomValue(0,3);
        
        for (int i = 0; i < 30; i++)
        {
            float angulo = anguloBase + i * (2 * PI / 24);

            projeteis[i].ativo = true;
            switch (atack_patern)
            {
            case 0:projeteis[i].area = (Rectangle){screenWidth / 4,10,12,12}; break;
            case 1:projeteis[i].area = (Rectangle){screenWidth*3/4,10,12,12}; break;
            case 2:projeteis[i].area = (Rectangle){screenWidth / 4, screenHeight - 10,12,12}; break;
            case 3:projeteis[i].area = (Rectangle){screenWidth*3/4, screenHeight - 10,12,12}; break;
            default:break;
            }

            // Velocidade baseada no ângulo para criar efeito espiral
            projeteis[i].velocidade = (Vector2){
                4 * cosf(angulo),
                4 * sinf(angulo)};
            projeteis[i].angulo = angulo;
        }

        for (int i = 25; i < 60; i++)
        {
            float angulo = anguloBase + i * (2 * PI / 24);

            projeteis[i].ativo = true;
            switch (atack_patern)
            {
            case 0:projeteis[i].area = (Rectangle){screenWidth,screenHeight*3/4,12,12}; break;
            case 1:projeteis[i].area = (Rectangle){10,screenHeight*3/4,12,12}; break;
            case 2:projeteis[i].area = (Rectangle){screenWidth, screenHeight/4,12,12}; break;
            case 3:projeteis[i].area = (Rectangle){10,screenHeight /4,12,12}; break;
            default:break;
            }

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
        int atack_patern = GetRandomValue(0,2);

        switch (atack_patern)
        {
        case 0:// Projéteis que convergem de todos os lados para o centro e depois divergem
        for (int i = 0; i < 45; i++)
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
            float velocidade = GetRandomValue(8, 12);
            projeteis[i].velocidade = (Vector2){
                (dx / dist) * velocidade,
                (dy / dist) * velocidade};

            // Ângulo para rotação do projétil
            projeteis[i].angulo = atan2f(dy, dx);
        }
            break;
        case 1:
            for(int j = 0; j < 5; j++) {
                for (int i = 0 + j*20; i < 20 + j*20; i++)
                {
                    projeteis[i].ativo = true;
                    projeteis[i].area = (Rectangle){GetRandomValue(50 + (screenWidth*j/5), screenWidth/10 + (screenWidth*j/5)),10, 15, 15};
                    projeteis[i].velocidade = (Vector2){
                        0,
                        GetRandomValue(15, 25)   // Velocidade vertical variável
                    };
                    projeteis[i].angulo = 0;
                }
            }
            break;
        case 2:
            for(int j = 0; j < 5; j++) {
                for (int i = 0 + j*20; i < 20 + j*20; i++)
                {
                    projeteis[i].ativo = true;
                    projeteis[i].area = (Rectangle){10,GetRandomValue(50 + (screenHeight*j/5), screenHeight/10 + (screenHeight*j/5)), 15, 15};
                    projeteis[i].velocidade = (Vector2){
                        GetRandomValue(15, 25),
                        0   // Velocidade vertical variável
                    };
                    projeteis[i].angulo = 0;
                }
            }
            break;
        
        default:
            break;
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

void updateBoss(Boss *boss, Rectangle area_boss, Projetil projeteis[], int *cooldown_atk, int *acertou_palavra, int dano_ataque)
{
    // Atualiza o padrão baseado na vida atual do boss
    if (boss->vida > 140)
        boss->padrao_atual = 0;
    else if (boss->vida > 70)
        boss->padrao_atual = 1;
    else{
        boss->padrao_atual = 2;
        boss->cooldown_atk = 240;
    }
    drawBoss(boss, area_boss.x, area_boss.y);

    // Verificar se acertou a palavra
    if (*acertou_palavra == 1)
    {
        boss->vida -= dano_ataque;
        if (boss->vida < 0)
            boss->vida = 0;
        (*acertou_palavra) = 0;
    }
    
    if (*cooldown_atk >= boss->cooldown_atk)
    {
        gerarPadraoAtaque(boss, projeteis, boss->padrao_atual);
        *cooldown_atk = 0;
    }
    else (*cooldown_atk)++;  

    atualizarProjeteis(boss, projeteis);
}
