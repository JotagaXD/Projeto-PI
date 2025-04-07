#include <stdio.h>
#include <raylib.h>
#include "draw.h"

void drawKeyboard(Vector2 *keyboard, Texture2D *keys, int target) {
    for (int i = 0; i < 26; i++){
        if (i != target){
            DrawRectangle(keyboard[i].x, keyboard[i].y, 70, 70, WHITE);
            DrawTexture(keys[i], keyboard[i].x, keyboard[i].y, WHITE);
        } else {
            Color random = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
            
           DrawRectangle(keyboard[i].x, keyboard[i].y, 70, 70, random);
        }
    }
}

void DrawUpLife(char *str_cura, bool *up_life, int *opacidade, int *scroll1, int *cura){
    if (*opacidade < 255){
        Color red_up = {255, 0, 0, 255 - *opacidade};
        DrawText(str_cura, 192, 100 - *scroll1, 60, red_up);
        *scroll1 += 2;
        *opacidade += 8;
    } else {
        *opacidade = 0;
        *up_life = false;
        *scroll1 = 0;     
    }
}

void DrawDownLife(char *str_dano, bool *down_life, int *opacidade, int *scroll1){
    if (*opacidade < 255){
        Color green_down = {0, 255, 0, 255 - *opacidade};
        DrawText(str_dano, 198, 180 + *scroll1, 60, green_down);
        *scroll1 += 2;
        *opacidade += 8;
    } else {
        *opacidade = 0;
        *down_life = false;
        *scroll1 = 0;
    }
}

void DrawTip(char *tip, int *timer2, int *scroll3, int *opacidade3){
    if (*timer2 < 60) {
        *timer2 = *timer2 + 1;
    } else if (*opacidade3 < 255 && *timer2 == 60){
        Color yellow_tip = {253, 249, 0, *opacidade3};
        DrawText(tip, 850 - strlen(tip)*10 + *scroll3, 350, 40, yellow_tip);
        *scroll3 += 2;
        *opacidade3 += 13;
    } else if (*timer2 < 180){ 
        *timer2 = *timer2 + 1;
        DrawText(tip, 850 - strlen(tip)*10 + *scroll3, 350, 40, YELLOW);
        *scroll3 += 1;
        *opacidade3 = 0;
    } else if (*opacidade3 < 255 && *timer2 == 180){
        Color yellow_tip = {253, 249, 0, 255 - *opacidade3};
        DrawText(tip, 850 - strlen(tip)*10 + *scroll3, 350, 40, yellow_tip);
        *scroll3 += 2;
        *opacidade3 += 13;
    } else {
        *scroll3 = 0;
        *opacidade3 = 0;
        *timer2 += 1;
    }
}

void DrawDownTime(char *str_timer_past, bool *down_time, int *opacidade2, int *scroll2){
    if (*opacidade2 < 255){
        Color red_down = {255, 255, 255, 255 - *opacidade2};
        DrawText(str_timer_past, 1530, 180 + *scroll2, 60, red_down);
        *scroll2 += 2;
        *opacidade2 += 8;
    } else {
        *opacidade2 = 0;
        *down_time = false;
        *scroll2 = 0;
    }
}
