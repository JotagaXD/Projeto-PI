#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include "sets.h"

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 30

#include <string.h>


char **read_words(char *arquivo, int *word_count) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }

    // Primeiro, conta quantas palavras existem no arquivo
    int total_words = 0;
    char buffer[MAX_WORD_LENGTH];
    while (fscanf(file, "%29s", buffer) == 1) {
        total_words++;
    }

    if (total_words == 0) {
        printf("O arquivo está vazio ou não contém palavras válidas\n");
        fclose(file);
        exit(1);
    }

    rewind(file);

    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        exit(1);
    }

    *word_count = 0;

    // Lê palavras aleatórias até preencher MAX_WORDS ou acabar o arquivo
    while (*word_count < MAX_WORDS) {
        // Escolhe uma posição aleatória no arquivo
        int random_pos = rand() % total_words;
        
        // Avança até a posição aleatória
        for (int i = 0; i < random_pos; i++) {
            if (fscanf(file, "%29s", buffer) != 1) {
                break; // Se falhar, sai do loop
            }
        }

        // Lê a palavra na posição aleatória
        if (fscanf(file, "%29s", buffer) == 1) {
            words[*word_count] = malloc(strlen(buffer) + 1);
            if (words[*word_count] == NULL) {
                printf("Erro ao alocar memória para a palavra\n");
                fclose(file);
                for (int i = 0; i < *word_count; i++) {
                    free(words[i]);
                }
                free(words);
                exit(1);
            }
            strcpy(words[*word_count], buffer);
            (*word_count)++;
        }

        // Volta ao início do arquivo para a próxima iteração
        rewind(file);
    }

    fclose(file);
    return words;
}

StringActions *define_words(StringActions* head, int *num_Ammo, char **words)
{
    for (int i = 0; i < 10; i++)
    {
        head = insertAtEnd(head, words[i], num_Ammo);
    }
    return head;
}