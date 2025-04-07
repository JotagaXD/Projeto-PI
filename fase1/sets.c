#include <stdio.h>
#include <raylib.h>
#include "sets.h"

void set_keyboard(Vector2 *keyboard) {
    for(int i = 0; i < 26; i++){
        if (i < 10){
            keyboard[i].x = 520 + 90*(i%10);
            keyboard[i].y = 470 + 80*(i/10);
        } else {
            keyboard[i].x = 520 + 90*((i-1)%9);
            keyboard[i].y = 470 + 80*((i-1)/9);
        }
    }
}

void set_file(FILE **words, FILE **tips) {
    words[0] = fopen("C:\\raylib\\raylib\\examples\\core\\words.txt", "r");
    tips[0] = fopen("C:\\raylib\\raylib\\examples\\core\\tips.txt", "r");
}

char **set_word() {
    char **aux = (char **) malloc (2 * sizeof(char *));
    if (aux == NULL){
        exit(1);
    }
    aux[0] = (char *) malloc (30 * sizeof(char));
    if (aux[0] == NULL){
        exit(1);
    }
    aux[1] = (char *) malloc (100 * sizeof(char));
    if (aux[1] == NULL){
        exit(1);
    }
    return aux;
}

void set_keys(Texture2D keys[26]){
    char nome[64];
    for (int i = 0; i < 26; i++){
        sprintf(nome,"C:\\raylib\\raylib\\examples\core\\sprites_key\\%csemfundo.png", 'A' + 1);
        keys[i] = LoadTexture(nome);
        if (keys[i].id == 0) {
            printf("Deu erro");
        }
    }
}
