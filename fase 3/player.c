#include "player.h"

Player CreatePlayer(int screenWidth, int screenHeight) {
    Player player;
    player.posicao.x = screenWidth/2; player.posicao.y = screenHeight/2;
    player.vida = 0; player.index_cursor = -1;
    return player;
}

void UpdatePlayer(Player *player, Rectangle *textbox, StringActions *head, float dt) {
    if (IsKeyDown(KEY_RIGHT)) player->posicao.x += 400*dt;
    if (IsKeyDown(KEY_LEFT)) player->posicao.x -= 400*dt;
    if (IsKeyDown(KEY_DOWN)) player->posicao.y += 400*dt;
    if (IsKeyDown(KEY_UP)) player->posicao.y -= 400*dt;

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
    
}   

void DrawPlayer(Player player) {
    Rectangle playerRect = {player.posicao.x - 20, player.posicao.y - 40, 40.0f, 40.0f };
    DrawRectangleRec(playerRect, RED);
}
