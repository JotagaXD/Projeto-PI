#include "player.h"

void UpdatePlayer(Player *player, float dt) {
    //Vector2 movimento = {0};
    if (IsKeyDown(KEY_RIGHT)) player->posicao.x += 300*dt;
    if (IsKeyDown(KEY_LEFT)) player->posicao.x -= 300*dt;
    if (IsKeyDown(KEY_DOWN)) player->posicao.y += 300*dt;
    if (IsKeyDown(KEY_UP)) player->posicao.y -= 300*dt;
    //if ((IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) || (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))) {}
}   

void DrawPlayer(Player player) {
    Rectangle playerRect = {player.posicao.x - 20, player.posicao.y - 40, 40.0f, 40.0f };
    DrawRectangleRec(playerRect, RED);
}

void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, Rectangle *textbox, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->posicao.x < bboxWorldMin.x) camera->target.x = player->posicao.x; textbox->x = player->posicao.x;
    if (player->posicao.y < bboxWorldMin.y) camera->target.y = player->posicao.y; textbox->y = player->posicao.y;
    if (player->posicao.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x); textbox->x = bboxWorldMin.x + (player->posicao.x - bboxWorldMax.x);
    if (player->posicao.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y); textbox->y = bboxWorldMin.y + (player->posicao.y - bboxWorldMax.y);
}