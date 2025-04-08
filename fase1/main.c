#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sets.h"
#include "gets.h"
#include "draw.h"
#include "update.h"
#include "tasks.h"

int main () {

    Vector2 keyboard[26];
    set_keyboard(keyboard);  // define as posições de cada tecla do teclado na interface do jogo
    Texture2D keys[26];
    Texture2D mole;

    FILE *words, *tips;
    set_file(&words, &tips);  // seta os ponteiros dos arquivos
    
    int sel = -1, target = -1, timer1 = 0, timer2 = 0, clk = 0, timer3 = 0, interval1 = 50, interval2 = 20, idx = 0, life = 100, scroll1 = 0, cura, opacidade1 = 0, opacidade2 = 0, scroll2 = 0, scroll3 = 0, opacidade3 = 0;
    
    char **word = set_word(), str_life[4], str_dano[4], str_cura[4], str_timer[8], str_timer_past[8], str_tips[100];
    
    bool end = false, read = true, up_life = false, down_life = false, down_time = false, change = false;
    
    InitWindow(1920, 1080, "My first RAYLIB program!");

    set_keys(keys);
    mole = LoadTexture("sprites\\sprites_toupeira\\toupeirafinal.png");

    SetTargetFPS(60);

    // game loop
    while (WindowShouldClose() == false && end == false && timer3 < 120){
        // event holding

        upd_timer(&timer3, &clk, &down_time);   // atualiza um clock de 1hz
        
        upd_str_timer(str_timer, timer3, str_timer_past, down_time);  // atualiza as strings que recebem os caracteres que representam o tempo

        task_read(&read, &change, word, str_tips, words, tips, &timer1, timer2, &idx);

        task_tips(&change, &timer2, str_tips, word);
        
        task_mole(&read, &up_life, &timer1, &interval1, &interval2, &target, &idx, &cura, &life, word, str_cura);
        
        get_key(&sel);  // verifica e retorna a tecla a qual o usuário pressionou
        
        get_rit(&down_life, &read, &target, &life, sel, str_dano);
        
        if (life < 1 && down_life == false) end = true;   // verifica se a toupeira foi derrotada -> vida igual a 0
        
        snprintf(str_life, sizeof(str_life), "%d", life);    // atualiza a string da vida

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        drawKeyboard(keyboard, keys, mole, target, sel);  // desenha o teclado
        if (up_life == true){
            DrawUpLife(str_cura, &up_life, &opacidade1, &scroll1, &cura); // animação de cura
        }
        if (down_life == true){
            DrawDownLife(str_dano, &down_life, &opacidade1, &scroll1);  // animação de dano
        }
        if (down_time == true){ 
            DrawDownTime(str_timer_past, &down_time, &opacidade2, &scroll2);  // animação do tempo
        }
        DrawText("BOSS", 105, 144, 30, WHITE);
        DrawText(str_life, 210, 140, 60, WHITE);
        DrawTip(str_tips, &timer2, &scroll3, &opacidade3); // animação da dica
        DrawText(str_timer, 1530, 140, 60, WHITE);
        DrawText("TIMER", 1698, 144, 30, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
