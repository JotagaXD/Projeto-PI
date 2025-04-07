#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sets.h"
#include "gets.h"
#include "draw.h"
#include "update.h"

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

        if (read == true){    // busca de uma nova palavra no arquivo
            word = get_fromFile(words, tips, word);    // busca uma palavra aleatória do arquivo 
            if (timer2 == 0) strcpy(str_tips, word[1]);   // verifica se a frase da dica ainda não foi exibida
            rewind(words);   // seta o ponteiro do arquivo para o inicio do arquivo
            rewind(tips);
            timer1 = 0;
            if (timer2 != 0) change = true;   // verifica se uma nova dica deve aparecer na tela
            idx = 0;
            read = false;
        }

        if (timer2 > 180){    // se não há mais dicas na tela
            if (change) {   // e uma nova dica tem que ser mostrada, atualiza a dica a ser mostrada
                timer2 = 0;
                change = false;
                strcpy(str_tips, word[1]);
            }
        }
        
        if (timer1 < interval1){  // definição do tempo de aparição da toupeira
            timer1++;
        } else if (timer1 < interval1 + interval2){  // tempo em que a toupeira se mantém à mostra
            timer1++;
            if (target == -1) {   // se a tecla a qual a toupeira apareceu, foi apertada, deve definida a proxima tecla que a toupeira vai aparecer
                target = get_target(word[0][idx]);
                idx++;
            }
        } else {   // caso a tecla não seja apertada enquanto a toupeira estava à mostra
            interval1 = GetRandomValue(20,100);   // define novos intervalos de tempo de espera
            interval2 = GetRandomValue(10, 30);
            target = -1;
            timer1 = 0;
            if (idx == strlen(word[0])){   // se a toupeira conseguir formar a palavra
                read = true;
                cura = (strlen(word[0]) > 10)? 40 : (strlen(word[0]) > 5)? 30 : 20;  // atribui uma cura relacionada ao tamanho da palavra
                life += cura;
                if (life > 120) life = 120;  // quantidade de vida máxima
                snprintf(str_cura, sizeof(str_cura), "+%d", cura);  // atualização da string cura
                up_life = true;  // indica a animação da cura
            }
        }
        
        get_key(&sel);  // verifica e retorna a tecla a qual o usuário pressionou
        
        if (target == sel && target != -1){  // verifica se o usuário apertou a tecla que a toupeira está
            down_life = true;   // indica a animação do dano 
            read = true;
            snprintf(str_dano, sizeof(str_dano), "-10");
            life -= 10;
            target = -1;
        }
        
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
