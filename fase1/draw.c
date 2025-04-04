#include <stdio.h>
#include <raylib.h>
#include "draw.h"

void drawKeyboard(Vector2 *keyboard, int target) {
    for (int i = 0; i < 26; i++){
        if (i != target){
            DrawRectangle(keyboard[i].x, keyboard[i].y, 70, 70, WHITE);
            if (i == 0) DrawText("Q", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 1) DrawText("W", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 2) DrawText("E", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 3) DrawText("R", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 4) DrawText("T", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 5) DrawText("Y", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 6) DrawText("U", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 7) DrawText("I", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 8) DrawText("O", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 9) DrawText("P", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 10) DrawText("A", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 11) DrawText("S", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 12) DrawText("D", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 13) DrawText("F", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 14) DrawText("G", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 15) DrawText("H", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 16) DrawText("J", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 17) DrawText("K", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 18) DrawText("L", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 19) DrawText("Z", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 20) DrawText("X", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 21) DrawText("C", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 22) DrawText("V", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 23) DrawText("B", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 24) DrawText("N", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
            else if (i == 25) DrawText("M", keyboard[i].x + 25, keyboard[i].y + 25, 30, BLACK);
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