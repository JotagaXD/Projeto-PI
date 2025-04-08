#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum GameScreen { MENU = 0, FASE1, FASE2, JOGO_COMPLETO, CREDITOS } GameScreen;

int main(){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Menu");

    GameScreen currentScreen = MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (currentScreen == MENU)
        {
            Vector2 mousePoint = GetMousePosition();
            Rectangle botaofasetoupeira = { screenWidth/2 - 100, 150, 200, 50 };
            Rectangle botaofaseboss = { screenWidth/2 - 100, 220, 200, 50 };
            Rectangle botaojogocompleto = { screenWidth/2 - 100, 290, 200, 50 };
            Rectangle botaocreditos = { screenWidth/2 - 100, 360, 200, 50 };
            if (CheckCollisionPointRec(mousePoint, botaofasetoupeira) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                currentScreen = FASE1;
            else if (CheckCollisionPointRec(mousePoint, botaofaseboss) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                currentScreen = FASE2;
            else if (CheckCollisionPointRec(mousePoint, botaojogocompleto) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                currentScreen = JOGO_COMPLETO;
            else if (CheckCollisionPointRec(mousePoint, botaocreditos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                currentScreen = CREDITOS;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
            case MENU:
                DrawText("MAIN MENU", screenWidth/2 - MeasureText("MAIN MENU", 20)/2, 80, 20, DARKGRAY);
                DrawRectangle(screenWidth/2 - 100, 150, 200, 50, LIGHTGRAY);
                DrawText("Fase 1 - Toupeira", screenWidth/2 - MeasureText("Fase 1 - Toupeira", 20)/2, 165, 20, BLACK);

                DrawRectangle(screenWidth/2 - 100, 220, 200, 50, LIGHTGRAY);
                DrawText("Fase 2 - Boss", screenWidth/2 - MeasureText("Fase 2 - Boss", 20)/2, 235, 20, BLACK);

                DrawRectangle(screenWidth/2 - 100, 290, 200, 50, LIGHTGRAY);
                DrawText("Jogo Completo", screenWidth/2 - MeasureText("Jogo Completo", 20)/2, 305, 20, BLACK);

                DrawRectangle(screenWidth/2 - 100, 360, 200, 50, LIGHTGRAY);
                DrawText("Créditos", screenWidth/2 - MeasureText("Créditos", 20)/2, 375, 20, BLACK);
                break;

            case FASE1:
                DrawText("FASE 1 - Jogo toupeira...", 200, 280, 20, DARKBLUE);
                DrawText("Pressione ESC para voltar ao menu", 200, 320, 16, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;
                break;

            case FASE2:
                DrawText("FASE 2 - Boss...", 200, 280, 20, DARKGREEN);
                DrawText("Pressione ESC para voltar ao menu", 200, 320, 16, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;
                break;

            case JOGO_COMPLETO:
                DrawText("JOGO COMPLETO: Fase toupeira...", 200, 240, 20, DARKBLUE);
                DrawText("Fase boss...", 200, 280, 20, DARKGREEN);
                DrawText("Pressione ESC para voltar ao menu", 200, 320, 16, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;
                break;

            case CREDITOS:
                DrawText("Créditos:", 200, 240, 20, DARKGRAY);
                DrawText("Desenvolvido por grupo1 de pi", 200, 280, 20, BLACK);
                DrawText("Pressione ESC para voltar ao menu", 200, 320, 16, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;
                break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}