#include "player.h"

Player CreatePlayer(int screenWidth, int screenHeight) {
    Player player;
    player.posicao.x = screenWidth/2; player.posicao.y = screenHeight/2;
    player.posicao.height = 40; player.posicao.width = 40;
    player.vida = 100; player.index_cursor = -1;
    return player;
}

void UpdatePlayer(Player *player, Rectangle *textbox, StringActions *head, float dt) {
    if (IsKeyDown(KEY_RIGHT)) player->posicao.x += 400*dt;
    if (IsKeyDown(KEY_LEFT)) player->posicao.x -= 400*dt;
    if (IsKeyDown(KEY_DOWN)) player->posicao.y += 400*dt;
    if (IsKeyDown(KEY_UP)) player->posicao.y -= 400*dt;

    if (player->posicao.y < 0)
        player->posicao.y = 0;
    if (player->posicao.y > 1080 - 40)
        player->posicao.y = 1080 - 40;
    if (player->posicao.x < 0 + 20)
        player->posicao.x = 0+ 20;
    if (player->posicao.x > 1920 - 20)
        player->posicao.x = 1920 - 20;

    int word_size = MeasureText(head->string, 30);
    int word_lenght = strlen(head->string);

    float text_pos_x = player->posicao.x + 5 - word_size/2;
    float text_pos_y = player->posicao.y - 80.0f;

    textbox->x = text_pos_x;
    textbox->y = text_pos_y;

    DrawText(head->string, text_pos_x, text_pos_y, 30, LIGHTGRAY);

    for (int i = 0; i < word_lenght; i++) {
        char letter[2] = { head->string[i], '\0' };
        int lettersize = MeasureText(letter, 30);
        if (i <= player->index_cursor) {
            DrawText(TextFormat("%c", head->string[i]), text_pos_x, text_pos_y, 30, YELLOW);
        }
        else {
            DrawText(TextFormat("%c", head->string[i]), text_pos_x, text_pos_y, 30, RED);
        }
        text_pos_x += lettersize + 3;
    }
    
    DrawText(TextFormat("%d/100", player->vida), 10, 10, 40, GREEN);
}   

void DamagePlayer(Player *player, Projetil *projeteis, int *invincibility) {
    if (*invincibility <= 0)
        {
            for (int i = 0; i < 50; i++) //MAX PROJETEIS
            {
                if (projeteis[i].ativo && CheckCollisionRecs(player->posicao, projeteis[i].area))
                {
                    player->vida -= 10;
                    (*invincibility) = 120; // 2 segundos de invencibilidade
                    projeteis[i].ativo = false;
                    break;
                }
            }
        }
    else
    {
        (*invincibility)--;
    }
}

void DrawPlayer(Player player) {
    Rectangle playerRect = {player.posicao.x - 20, player.posicao.y - 40, 40.0f, 40.0f };
    DrawRectangleRec(playerRect, RED);
}

void TempStringUpdt(Color *temp_yellow, Rectangle *temp_string_rect, bool *yellow_done) {
    if (*yellow_done == true) {
        temp_string_rect->y -= 1;
        temp_yellow->a -= 5;
        if (temp_yellow->a == 0) {
            (*yellow_done) = false;
            temp_yellow->a = 255;
        }
    }
}
