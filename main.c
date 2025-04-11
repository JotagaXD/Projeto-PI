#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "menu.h"
#include "fase1.h"
#include "fase2.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 20

int main () {
    int init = 0;
    int state = 0;
    bool win = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BLAU");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {   
        if (init == 0) {
            menu(&init, &state);
        }
        else {
            switch (state)
            {
            case 1:
                fase1(&init, &win, state);
                break;
            case 2:
                fase2(&init, &win);
                break;
            case 3:
                fase1(&init, &win, state);
                if (win){
                    fase2(&init, &win);
                }
                break;
            default:
                break;
            }
        }
    }

    CloseWindow();

    return 0;
}
