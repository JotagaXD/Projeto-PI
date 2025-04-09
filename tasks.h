#ifndef TASKS_H
#define TASKS_H
#include <raylib.h>
#include <stdlib.h>
#include "tasks.c"

void task_read(bool *read, bool *change, char **word, char *str_tips, FILE *words, FILE *tips, int *timer1, int timer2, int *idx);
void task_tips(bool *change, int *timer2, char *str_tips, char **word);
void task_mole(bool *read, bool *up_life, int *timer1, int *interval1, int *interval2, int *target, int *idx, int *cura, int *life, char **word, char *str_cura);
void get_rit(bool *down_life, bool *read, int *target, int* life, int sel, char *str_dano);

#endif