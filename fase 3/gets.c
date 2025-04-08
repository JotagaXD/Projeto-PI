#include <stdio.h>
#include <raylib.h>
#include "gets.h"

char *get_fromFile(FILE *words, char *word){
    int n_word = GetRandomValue(0, 91);
    char aux[30];
    for (int i = 0; i < n_word; i++){
        fscanf(words, "%29s", aux);
    }
    //strcpy(word, aux);
    return word;
}