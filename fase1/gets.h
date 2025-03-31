#ifndef GETS_H
#define GETS_H

#include <raylib.h>
#include <stdlib.h>
#include "gets.c"

char **get_fromFile(FILE *words, FILE *tips, char **word);
int get_target(char letter);
void get_key(int *sel);
    
#endif