#include "fase2.h"

#define MAX_INPUT_CHARS    25
#define PLAYER_H_SPEED 5

bool fase2 (int *init) {
    int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Test");

    Color temp_yellow = { 253, 249, 0, 255 };
    bool yellow_done = false;
    Rectangle temp_string_rect;
    char temp_string[30];
    
    //organizar o arquivo de palavras
    char *arquivo = "words.txt";
    int word_count = 0;
    char **words = read_words(arquivo, &word_count);
    
    //organiza a lista encadeada
    char action_string[MAX_INPUT_CHARS + 1] = "\0";
    StringActions* head = NULL;
    int num_ammo = 0;
    head = define_words(head, &num_ammo, words);

    //rect das palavras do player
    Rectangle textbox;
    textbox.width = 550; textbox.height = 30;

    //seta o player
    Player player = CreatePlayer(screenWidth, screenHeight);
    int invincibility = 0; // Frames de invencibilidade após ser atingido
    int dano_ataque_palavra;

    // Inicialização do boss
    Boss boss;
    initBoss(&boss, 200, 5, 10, 180); // vida, velocidade_ataque, ataque, cooldown_atk/3 = seg
    // Área do boss
    Rectangle area_boss = {screenWidth - 100, screenHeight / 2 - 25, 50, 50};
    int cooldown_atk = 0;

    // Array de projéteis
    Projetil projeteis[MAX_PROJETEIS];
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        projeteis[i].ativo = false;
    }

    EnvItem envItems[5];
    for (int i = 0; i<5; i++) {
        envItems[i].rect.x = (screenWidth/2 - 375) + i*150; envItems[i].rect.y = screenHeight - 50; envItems[i].rect.width = 150; envItems[i].rect.height = 30; envItems[i].color = GRAY;
    }

    int acertou_palavra = 0;
    int string_size;

    while(!WindowShouldClose() && player.vida >= 0 && boss.vida >= 0) {
        float dt = GetFrameTime();

        string_size = strlen(head->string);
        if (string_size > 9) dano_ataque_palavra = string_size*3;
        else if (string_size > 6) dano_ataque_palavra = string_size*2;
        else dano_ataque_palavra = string_size;

        if (num_ammo == 5) {word_count = 0; words = read_words(arquivo, &word_count); head = define_words(head, &num_ammo, words);}

        UpdateTextbox(&head, action_string, temp_string, &player, &num_ammo, &acertou_palavra);
        UpdatePlayer(&player, &textbox, head, dt);
        DamagePlayer(&player, projeteis, &invincibility);
        
        BeginDrawing();
            ClearBackground(WHITE);
            
            if (acertou_palavra == 1) {
                temp_string_rect = textbox;
                yellow_done = true;
            }
            
            if (yellow_done) DrawText(temp_string, temp_string_rect.x, temp_string_rect.y, 30, temp_yellow);
            TempStringUpdt(&temp_yellow, &temp_string_rect, &yellow_done);
            
            if (invincibility <= 0 || (invincibility / 10) % 2 == 0)
            {
                DrawPlayer(player);
            }
            
            updateBoss(&boss, area_boss, projeteis, &cooldown_atk, &acertou_palavra, dano_ataque_palavra);

            for (int i = 0; i < 5; i++) { 
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleLines((int)envItems[i].rect.x, (int)envItems[i].rect.y, (int)envItems[i].rect.width, (int)envItems[i].rect.height, DARKGRAY);
            }
            DrawList(head, num_ammo, envItems);
            
        EndDrawing();
    }
    *init = 0;
    if (player.vida <= 0) {
        return 0;
    }
    else if (boss.vida <= 0) {
        return 1;
    }
}
