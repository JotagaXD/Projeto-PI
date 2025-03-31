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
    set_keyboard(keyboard);

    FILE *words, *tips;
    set_file(&words, &tips);
    
    int sel = -1, target = -1, timer1 = 0, timer2 = 0, clk = 0, timer3 = 0, interval1 = 50, interval2 = 20, idx = 0, life = 100, scroll1 = 0, cura, opacidade1 = 0, opacidade2 = 0, scroll2 = 0;
    
    char **word = set_word(), str_life[4], str_dano[4], str_cura[4], str_timer[8], str_timer_past[8];
    
    bool end = false, read = true, up_life = false, down_life = false, down_time = false;
    
    InitWindow(1920, 1080, "My first RAYLIB program!");
    SetTargetFPS(60);

    // game loop
    while (WindowShouldClose() == false && end == false && timer3 < 120){
        // event holding

        upd_timer(&timer3, &clk, &down_time);
        
        upd_str_timer(str_timer, timer3, str_timer_past, down_time);

        if (read == true){
            word = get_fromFile(words, tips, word);
            rewind(words);
            rewind(tips);
            timer1 = 0;
            timer2 = 0;
            idx = 0;
            read = false;
        }
        
        if (timer1 < interval1){
            timer1++;
        } else if (timer1 < interval1 + interval2){
            timer1++;
            if (target == -1) {
                target = get_target(word[0][idx]);
                idx++;
            }
        } else {
            interval1 = GetRandomValue(20,100);
            interval2 = GetRandomValue(10, 30);
            target = -1;
            timer1 = 0;
            if (idx == strlen(word[0])){
                read = true;
                cura = (strlen(word[0]) > 10)? 40 : (strlen(word[0]) > 5)? 30 : 20;
                snprintf(str_cura, sizeof(str_cura), "+%d", cura);
                up_life = true;
            }
        }
        
        get_key(&sel);
        
        if (target == sel && target != -1){
            down_life = true;
            read = true;
            snprintf(str_dano, sizeof(str_dano), "-10");
            life -= 10;
            target = -1;
        }
        
        if (life < 1 && down_life == false) end = true;
        
        snprintf(str_life, sizeof(str_life), "%d", life);

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        drawKeyboard(keyboard, target);
        if (up_life == true){
            DrawUpLife(str_cura, &up_life, &opacidade1, &scroll1, &life, &cura);
        }
        if (down_life == true){
            DrawDownLife(str_dano, &down_life, &opacidade1, &scroll1);
        }
        if (down_time == true){
            DrawDownTime(str_timer_past, &down_time, &opacidade2, &scroll2);
        }

        DrawText("BOSS", 105, 144, 30, WHITE);
        DrawText(str_life, 210, 140, 60, WHITE);
        DrawTip(word[1], &timer2);
        DrawText(str_timer, 1530, 140, 60, WHITE);
        DrawText("TIMER", 1698, 144, 30, WHITE);
        EndDrawing();
       
    }
    CloseWindow();
    return 0;
}