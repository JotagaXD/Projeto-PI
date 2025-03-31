#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include <stdlib.h>
#include "draw.c"

void drawKeyboard(Vector2 *keyboard, int target);
void DrawUpLife(char *str_cura, bool *up_life, int *opacidade, int *scroll1);
void DrawDownLife(char *str_dano, bool *down_life, int *opacidade, int *scroll1);
void DrawTip(char *tip, int *timer);
void DrawDownTime(char *str_timer_past, bool *down_time, int *opacidade2, int *scroll2);

#endif