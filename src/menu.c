#include "../include/menu.h"

void desenharMenu() {
    ClearBackground(BLACK);
    DrawText("MENU DO JOGO", 200, 150, 40, WHITE);
    DrawText("Pressione ENTER para iniciar", 180, 250, 20, GRAY);
}

int verificarInicio() {
    return IsKeyPressed(KEY_ENTER);
}
