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
    int screenWidth = 1920, screenHeight = 1080;
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

    Player player;
    player.posicao.x = 10;
    player.posicao.y = screenHeight/2;

    /*Camera2D camera = { 0 };
    camera.target = player.posicao;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;*/

    EnvItem envItems[5];
    for (int i = 0; i<5; i++) {
        envItems[i].rect.x = (screenWidth/2 + 225) - i*150; envItems[i].rect.y = screenHeight - 30; envItems[i].rect.width = 150; envItems[i].rect.height = 30; envItems[i].color = GRAY;
    }

    SetTargetFPS(60);
    ToggleFullscreen();

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        ClearBackground(WHITE);

        //word = get_fromFile(words, word);****************

        UpdatePlayer(&player, &textbox, action_string, dt);
        UpdateTextbox(head, action_string, &letterCount, Num_ammo);

        BeginDrawing();
            DrawPlayer(player);
            DrawText(action_string, (int)textbox.x + 1, (int)textbox.y + 3, 30, MAROON);
            if (head!=NULL) DrawText(head->string, (int)textbox.x + 1, (int)textbox.y + 3, 30, LIGHTGRAY);
            for (int i = 0; i < 5; i++) { 
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleLines((int)envItems[i].rect.x, (int)envItems[i].rect.y, (int)envItems[i].rect.width, (int)envItems[i].rect.height, DARKGRAY);
            }
            //DrawList(head, Num_ammo, envItems);*********
        EndDrawing();
    }

    return 0;
}