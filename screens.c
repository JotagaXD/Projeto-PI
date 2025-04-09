#include "screens.h" 

void wins(){
    Texture2D win_screen = LoadTexture("sprites/win_screen.png");
    while(!IsKeyPressed(KEY_M)){
        BeginDrawing();
        DrawTexture(win_screen, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(win_screen);
}

void defeat(){
    Texture2D defeat_screen = LoadTexture("sprites/defeat_screen.png");
    while(!IsKeyPressed(KEY_M)){
        BeginDrawing();
        DrawTexture(defeat_screen, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(defeat_screen);
}

void instruction1(){
    Texture2D inst1 = LoadTexture("sprites/instruction1.png");
    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        DrawTexture(inst1, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(inst1);
}

void lore(){
    char *line1 = "Voce e um aluno dedicado da disciplina de Programacao Imperativa. Estava concentrado";
    char *line2 = "escrevendo seu codigo, quando de repente algo estranho aconteceu: uma toupeira";
    char *line3 = "pixelada surgiu na tela, baguncando suas linhas de programacao!";
    char *line4 = "Assustada, ela comecou a digitar palavras sem sentido, inserindo erros nos seus";
    char *line5 = "scripts. Aparentemente, trata-se de um virus em forma de toupeira digital, que so";
    char *line6 = "pode ser derrotado com agilidade e precisao no teclado.";
    char *line7 = "Agora, sua missao e combater essa ameaca antes que ela corrompa todo o seu";
    char *line8 = "projeto. Prepare-se para digitar com velocidade e acabar com o caos!";
    char type[702];
    while(!IsKeyPressed(KEY_SPACE)){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(line1, 70, 100, 40, WHITE);
        DrawText(line2, 70, 150, 40, WHITE);
        DrawText(line3, 70, 200, 40, WHITE);
        DrawText(line4, 70, 250, 40, WHITE);
        DrawText(line5, 70, 300, 40, WHITE);
        DrawText(line6, 70, 350, 40, WHITE);
        DrawText(line7, 70, 400, 40, WHITE);
        DrawText(line8, 70, 450, 40, WHITE);
        DrawText("Pressione ESPACO para continuar", 100, 800, 40, WHITE);
        EndDrawing();
    }
}