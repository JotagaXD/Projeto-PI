#include <stdio.h>
#include <raylib.h>
#include "sets.h"

void set_file(FILE **words) {
    words[0] = fopen("C:/raylib/raylib/examples/core/words.txt", "r");
}

char *set_word() {
    char *aux = (char *) malloc (30 * sizeof(char));
    if (aux == NULL){
        exit(1);
    }

    return aux;
}