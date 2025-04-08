#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "string_func.h"
#include "gets.h"
#include "sets.h"
#include "boss.h"

#define MAX_INPUT_CHARS    25
#define PLAYER_H_SPEED 5

int main () {
    int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Test");
    
    char *arquivo = "words.txt";
    int word_count = 0;
    char **words = read_words(arquivo, &word_count);
    
    char action_string[MAX_INPUT_CHARS + 1] = "\0";
    StringActions* head = NULL;
    int num_ammo = 0;
    head = define_words(head, &num_ammo, words);

    Rectangle textbox;
    textbox.width = 550; textbox.height = 30;

    Player player = CreatePlayer(screenWidth, screenHeight);

    Boss boss;
    initBoss(&boss, 100, 5, 5, 1);
    Rectangle area_tiro;
    area_tiro.width = 10; area_tiro.height = 10; area_tiro.x = screenWidth - 50; area_tiro.y = screenHeight/2;


    EnvItem envItems[5];
    for (int i = 0; i<5; i++) {
        envItems[i].rect.x = (screenWidth/2 - 375) + i*150; envItems[i].rect.y = screenHeight - 50; envItems[i].rect.width = 150; envItems[i].rect.height = 30; envItems[i].color = GRAY;
    }

    SetTargetFPS(60);
    ToggleFullscreen();

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        ClearBackground(WHITE);

        if (num_ammo == 5) {word_count = 0; words = read_words(arquivo, &word_count); head = define_words(head, &num_ammo, words);}

        UpdateTextbox(&head, action_string, &player, &num_ammo);
        updateBossAttack(&boss, &area_tiro);
        UpdatePlayer(&player, &textbox, head, dt);
        
        BeginDrawing();
            DrawPlayer(player);
            DrawText(head->string, 20, 20, 30, ORANGE);
            
            for (int i = 0; i < 5; i++) { 
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleLines((int)envItems[i].rect.x, (int)envItems[i].rect.y, (int)envItems[i].rect.width, (int)envItems[i].rect.height, DARKGRAY);
                drawBoss(&boss, screenWidth/2 - 100, 100);
            }
            DrawList(head, num_ammo, envItems);

        EndDrawing();
    }

    return 0;
}