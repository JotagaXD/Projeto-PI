#ifndef SETS_F2_H
#define SETS_F2_H
#include <raylib.h>
#include <stdlib.h>
#include "sets_f2.c"

char **read_words(char *arquivo, int *word_count);
StringActions *define_words(StringActions* head, int *num_Ammo, char **words);

#endif