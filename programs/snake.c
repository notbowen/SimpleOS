#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../libc/random.h"
#include "../cpu/timer.h"

#define LEFT   0x1E
#define RIGHT  0x20
#define UP     0x11
#define DOWN   0x1F

int gameOver;

const int width = 40;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

int dir = 0;   // 0 = STOP, 1 = LEFT, 2 = RIGHT, 3 = UP, 4 = DOWN

void Setup() {
    asm volatile ("sti");

    srand(getCurrentTick());

    gameOver = 0;
    dir = 0;

    x = width / 2;
    y = height / 2;
    nTail = 0;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

    clear_screen();
}

void Draw() {
    move_cursor(0);

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
                tprint("#");
            }
        }

        tprint("\n");
    }

    for (int i = 0; i < width + 2; i++) {
        tprint("#");
    }

    tprint("\n");
    tprint("Score: ");

    char scoreOutput[10];
    int_to_char(score, scoreOutput);
    tprint(scoreOutput);
    tprint("\n");

    tprint("[HELP] O: Player | F: Food | Movement: WASD | Quit: Q\n");

    tprint("[DEBUG] Current Tick: ");
    char tickOutput[256];
    int_to_char(getCurrentTick(), tickOutput);
    tprint(tickOutput);
}

void Input() {
    switch (lastPressed) {
        case LEFT:
            dir = 1;
            break;
        case RIGHT:
            dir = 2;
            break;
        case UP:
            dir = 3;
            break;
        case DOWN:
            dir = 4;
            break;
        case 0x10:     // Q
            gameOver = 1;
            break;
        default:
            break;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y= tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case 1:
            x--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        case 4:
            y++;
            break;
        default:
            break;
    }

    if (x > width|| x < 0 || y > height || y < 0) {
        gameOver = 1;
    }

    for (int i = 0;i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void snake_main() {
    Setup();

    while (gameOver == 0) {
        Draw();
        Input();
        Logic();

        sleep(5);

        // 1 in 5 chance of changing seed
        if (rand() % 5 == 1) {
            int seed = (int)getCurrentTick();
            srand(seed);
        }
    }

    clear_screen();
    tprint("End of game :D\nReturning to shell...");
    return;
}