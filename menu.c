#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "player.h"
#include "string_func.h"
#include "sets_f2.h"
#include "boss.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 20

void menu(int *init, int *state) {

    Texture2D background = LoadTexture("sprites/background.png");

    int currentScreen = 0;

    // Define botões
    Rectangle buttons[4];
    for (int i = 0; i < 4; i++) {
        buttons[i].width = BUTTON_WIDTH;
        buttons[i].height = BUTTON_HEIGHT;
        buttons[i].x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
        buttons[i].y = 300 + i * (BUTTON_HEIGHT + BUTTON_SPACING);
    }

    const char *buttonLabels[4] = {
        "Fase 1", "Fase 2", "Jogo Completo", "Créditos"
    };
        
    while (!WindowShouldClose() && *init == 0) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        if (currentScreen == 0) {
            for (int i = 0; i < 4; i++) {
                Color btnColor = CheckCollisionPointRec(mouse, buttons[i]) ? DARKGRAY : GRAY;
                DrawRectangleRec(buttons[i], btnColor);

                // Centralizar texto nos botões
                int textWidth = MeasureText(buttonLabels[i], 20);
                DrawText(buttonLabels[i],
                         buttons[i].x + (BUTTON_WIDTH - textWidth) / 2,
                         buttons[i].y + 15,
                         20, BLACK);

                // Clique
                if (CheckCollisionPointRec(mouse, buttons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = (i + 1);
                }
            }
        } else {
            switch (currentScreen) {
                case 1: *init = 1; *state = 1; break;
                case 2: *init = 1; *state = 2; break;
                case 3: *init = 1; *state = 3; break;
                case 4:  DrawText("Créditos: Arte gerada por IA", 550, 100, 40, YELLOW); break;
                default: break;
            }
            
            DrawText("Pressione ESC para voltar ao menu", 200, 340, 20, DARKGRAY);

            if (IsKeyPressed(KEY_ESCAPE)) {
                currentScreen = 0;
            }
        }
        EndDrawing();
    }

    UnloadTexture(background);
}
