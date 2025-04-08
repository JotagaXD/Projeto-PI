#ifndef SETS_H
#define SETS_H
#include <raylib.h>
#include <stdlib.h>
#include "sets.c"

char **read_words(char *arquivo, int *word_count);
StringActions *define_words(StringActions* head, int *num_Ammo, char **words);

#endif