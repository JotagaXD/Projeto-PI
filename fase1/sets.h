#ifndef SETS_H
#define SETS_H
#include <raylib.h>
#include <stdlib.h>
#include "sets.c"

void set_keyboard(Vector2 *keyboard);
void set_file(FILE **words, FILE **tips);
char **set_word();

#endif