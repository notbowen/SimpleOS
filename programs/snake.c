#include "../drivers/screen.h"
#include "../libc/random.h"

int gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

int dir = 0;   // 0 = STOP, 1 = LEFT, 2 = RIGHT, 3 = UP, 4 = DOWN

void Setup() {
    gameOver = 0;
    dir = 0;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
}

void Draw() {
    clear_screen();

    for (int i = 0; i < width + 2; i++) {
        tprint("#");
    }
    tprint("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                tprint("#");

            if (i == y && j == x) {
                tprint("O");
            } else if (i == fruitY && j == fruitX) {
                tprint("F");
            } else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        tprint("o");
                        print = 1;
                    }
                }

                if (!print)
                    tprint(" ");
            }

            if (j == width - 1) {
                tprint("#")
            }
        }

        tprint("\n");
    }

    for (int i = 0; i < width + 2; i++) {
        tprint("#");
    }

    tprint("\n");
    tprint("Score: ");


    
}