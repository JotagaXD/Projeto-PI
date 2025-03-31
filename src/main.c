#include "../include/Projeto_Jogo.h"

int main() {
    InitWindow(1920, 1080, "Meu Jogo");


    int jogoIniciado = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (!jogoIniciado) {
            desenharMenu();
            if (verificarInicio()) {
                jogoIniciado = 1;
            }
        } else {
            ClearBackground(RAYWHITE);
            DrawText("O jogo começou!", 250, 250, 30, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
