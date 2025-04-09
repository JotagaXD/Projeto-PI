#include <stdio.h>
#include <raylib.h>
#include "gets.h"

char **get_fromFile(FILE *words, FILE *tips, char **word){
    int n_word = GetRandomValue(0, 91);
    for (int i = 0; i < n_word; i++){
        fscanf(words, "%29s", word[0]);
        fscanf(tips, "%99[^\n]\n", word[1]);
    }
    return word;
}

int get_target(char letter) {
    int target;
    switch(letter){
        case 'q': target = 0; break;
        case 'w': target = 1; break;
        case 'e': target = 2; break;
        case 'r': target = 3; break;
        case 't': target = 4; break;
        case 'y': target = 5; break;
        case 'u': target = 6; break;
        case 'i': target = 7; break;
        case 'o': target = 8; break;
        case 'p': target = 9; break;
        case 'a': target = 10; break;
        case 's': target = 11; break;
        case 'd': target = 12; break;
        case 'f': target = 13; break;
        case 'g': target = 14; break;
        case 'h': target = 15; break;
        case 'j': target = 16; break;
        case 'k': target = 17; break;
        case 'l': target = 18; break;
        case 'z': target = 19; break;
        case 'x': target = 20; break;
        case 'c': target = 21; break;
        case 'v': target = 22; break;
        case 'b': target = 23; break;
        case 'n': target = 24; break;
        case 'm': target = 25; break;
        default: target = -1; break;
    }
    return target;
}

void get_key(int *sel){
    if (IsKeyDown(KEY_Q)) { *sel = 0; }
    else if (IsKeyDown(KEY_W)) { *sel = 1; }
    else if (IsKeyDown(KEY_E)) { *sel = 2; }
    else if (IsKeyDown(KEY_R)) { *sel = 3; }
    else if (IsKeyDown(KEY_T)) { *sel = 4; }
    else if (IsKeyDown(KEY_Y)) { *sel = 5; }
    else if (IsKeyDown(KEY_U)) { *sel = 6; }
    else if (IsKeyDown(KEY_I)) { *sel = 7; }
    else if (IsKeyDown(KEY_O)) { *sel = 8; }
    else if (IsKeyDown(KEY_P)) { *sel = 9; }
    else if (IsKeyDown(KEY_A)) { *sel = 10; }
    else if (IsKeyDown(KEY_S)) { *sel = 11; }
    else if (IsKeyDown(KEY_D)) { *sel = 12; }
    else if (IsKeyDown(KEY_F)) { *sel = 13; }
    else if (IsKeyDown(KEY_G)) { *sel = 14; }
    else if (IsKeyDown(KEY_H)) { *sel = 15; }
    else if (IsKeyDown(KEY_J)) { *sel = 16; }
    else if (IsKeyDown(KEY_K)) { *sel = 17; }
    else if (IsKeyDown(KEY_L)) { *sel = 18; }
    else if (IsKeyDown(KEY_Z)) { *sel = 19; }
    else if (IsKeyDown(KEY_X)) { *sel = 20; }
    else if (IsKeyDown(KEY_C)) { *sel = 21; }
    else if (IsKeyDown(KEY_V)) { *sel = 22; }
    else if (IsKeyDown(KEY_B)) { *sel = 23; }
    else if (IsKeyDown(KEY_N)) { *sel = 24; }
    else if (IsKeyDown(KEY_M)) { *sel = 25; }
    else { *sel = -1; }
}