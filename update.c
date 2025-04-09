#include <stdio.h>
#include <raylib.h>
#include "update.h"

void upd_timer(int *timer, int *clk, bool *down_time){
    if (*clk < 60){
        ++*clk;
    } else {
        *clk = 0;
        ++*timer;
        *down_time = true;
    }
}

void upd_str_timer(char *str_timer, int timer, char *str_timer_past, bool down_time) {
    if (timer/60) {
        if((timer - 60*(timer/60))/10){
            snprintf(str_timer, sizeof(str_timer), "0%d:%d\0", timer/60, timer - 60*(timer/60));
        } else {
            snprintf(str_timer, sizeof(str_timer), "0%d:0%d\0", timer/60, timer - 60*(timer/60));
        }
    } else {
        if((timer - 60*(timer/60))/10){
            snprintf(str_timer, sizeof(str_timer), "00:%d\0", timer - 60*(timer/60));
        } else {
            snprintf(str_timer, sizeof(str_timer), "00:0%d\0", timer - 60*(timer/60));
        }
    }
    if (down_time == false){
        strcpy(str_timer_past, str_timer);
    }
}