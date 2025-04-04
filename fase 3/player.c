#include "player.h"

void UpdatePlayer(Player *player, Rectangle *textbox, char *action_string, float dt) {
    if (IsKeyDown(KEY_RIGHT)) player->posicao.x += 300*dt;
    if (IsKeyDown(KEY_LEFT)) player->posicao.x -= 300*dt;
    if (IsKeyDown(KEY_DOWN)) player->posicao.y += 300*dt;
    if (IsKeyDown(KEY_UP)) player->posicao.y -= 300*dt;

    int word_size = MeasureText(action_string, 30);

    float text_pos_x = player->posicao.x - word_size/2;
    float text_pos_y = player->posicao.y - 100.0f;

    textbox->x = text_pos_x;
    textbox->y = text_pos_y;
}   

void DrawPlayer(Player player) {
    Rectangle playerRect = {player.posicao.x - 20, player.posicao.y - 40, 40.0f, 40.0f };
    DrawRectangleRec(playerRect, RED);
}

/*void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, , float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->posicao.x < bboxWorldMin.x) camera->target.x = player->posicao.x; 
    if (player->posicao.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x); textbox->x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x);
    if (player->posicao.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y); textbox->y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y);
}*/