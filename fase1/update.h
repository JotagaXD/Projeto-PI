#ifndef UPDATE_H
#define UPDATE_H

#include <raylib.h>
#include <stdlib.h>
#include "update.c"

void upd_timer(int *timer, int *clk, bool *down_time);

void upd_str_timer(char *str_timer, int timer, char *str_timer_past, bool down_time);

#endif