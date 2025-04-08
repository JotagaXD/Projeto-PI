#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

void task_read(bool *read, bool *change, char **word, char *str_tips, FILE *words, FILE *tips, int *timer1, int timer2, int *idx){
    if (*read == true){    // busca de uma nova palavra no arquivo
        word = get_fromFile(words, tips, word);    // busca uma palavra aleatória do arquivo 
        if (timer2 == 0) strcpy(str_tips, word[1]);   // verifica se a frase da dica ainda não foi exibida
        rewind(words);   // seta o ponteiro do arquivo para o inicio do arquivo
        rewind(tips);
        *timer1 = 0;
        if (timer2 != 0) *change = true;   // verifica se uma nova dica deve aparecer na tela
        *idx = 0;
        *read = false;
    }
}

void task_tips(bool *change, int *timer2, char *str_tips, char **word){
    if (*timer2 > 180){    // se não há mais dicas na tela
        if (*change) {   // e uma nova dica tem que ser mostrada, atualiza a dica a ser mostrada
            *timer2 = 0;
            *change = false;
            strcpy(str_tips, word[1]);
        }
    }
}

void task_mole(bool *read, bool *up_life, int *timer1, int *interval1, int *interval2, int *target, int *idx, int *cura, int *life, char **word, char *str_cura){
    if (*timer1 < *interval1){  // definição do tempo de aparição da toupeira
        ++*timer1;
    } else if (*timer1 < *interval1 + *interval2){  // tempo em que a toupeira se mantém à mostra
        ++*timer1;
        if (*target == -1) {   // se a tecla a qual a toupeira apareceu, foi apertada, deve definida a proxima tecla que a toupeira vai aparecer
            *target = get_target(word[0][*idx]);
            ++*idx;
        }
    } else {   // caso a tecla não seja apertada enquanto a toupeira estava à mostra
        *interval1 = GetRandomValue(20,100);   // define novos intervalos de tempo de espera
        *interval2 = GetRandomValue(10, 30);
        *target = -1;
        *timer1 = 0;
        if (*idx == strlen(word[0])){   // se a toupeira conseguir formar a palavra
            *read = true;
            *cura = (strlen(word[0]) > 10)? 40 : (strlen(word[0]) > 5)? 30 : 20;  // atribui uma cura relacionada ao tamanho da palavra
            *life += *cura;
            if (*life > 120) *life = 120;  // quantidade de vida máxima
            snprintf(str_cura, sizeof(str_cura), "+%d", *cura);  // atualização da string cura
            *up_life = true;  // indica a animação da cura
        }
    }
}

void get_rit(bool *down_life, bool *read, int *target, int* life, int sel, char *str_dano){
    if (*target == sel && *target != -1){  // verifica se o usuário apertou a tecla que a toupeira está
        *down_life = true;   // indica a animação do dano 
        *read = true;
        snprintf(str_dano, sizeof(str_dano), "-10");
        *life -= 10;
        *target = -1;
    }
}