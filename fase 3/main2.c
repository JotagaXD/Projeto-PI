#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "string_func.h"
#include "gets.h"
#include "sets.h"

#define MAX_INPUT_CHARS    25
#define PLAYER_H_SPEED 5

int main () {
    const int screenWidth = 800, screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Test");

    FILE *words;
    set_file(&words);
    char *word = set_word();
    
    char action_string[MAX_INPUT_CHARS + 1] = "\0";
    StringActions* head = NULL;
    int letterCount = 0;
    int Num_ammo = 0;

    Rectangle textbox;
    textbox.width = 550; textbox.height = 30;

    Player player = {0};

    Camera2D camera = { 0 };
    camera.target = player.posicao;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    EnvItem envItems[5] = {{{25, 400, 150, 30}, GRAY},{{175, 400, 150, 30}, GRAY},{{325, 400, 150, 30}, GRAY},{{475, 400, 150, 30}, GRAY},{{625, 400, 150, 30}, GRAY}};

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        ClearBackground(WHITE);

        word = get_fromFile(words, word);

        UpdatePlayer(&player, dt);
        UpdateCameraPlayerBoundsPush(&camera, &player, &textbox, dt, screenWidth, screenHeight);
        UpdateTextbox(head, action_string, &letterCount, Num_ammo);

        BeginDrawing();
            BeginMode2D(camera);
                DrawPlayer(player);
                DrawText(action_string, (int)textbox.x + 1, (int)textbox.y + 3, 30, MAROON);
                if (head!=NULL) DrawText(head->string, (int)textbox.x + 1, (int)textbox.y + 3, 30, LIGHTGRAY);
            EndMode2D();
            
            for (int i = 0; i < 5; i++) { 
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleLines((int)envItems[i].rect.x, (int)envItems[i].rect.y, (int)envItems[i].rect.width, (int)envItems[i].rect.height, DARKGRAY);
                DrawList(head, Num_ammo, envItems);
            }
        EndDrawing();
    }

    return 0;
}