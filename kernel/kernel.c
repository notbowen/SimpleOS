#include "../drivers/screen.h"

void main() {
    clear_screen();

    for (int i = 0; i < MAX_ROWS; i++) {
        tprint("Hello World!\n");
    }

    for(int i = 0; i < 5; i++) {
        tprint("Scroll test\n");
    }

    tprint_char('\n');
    tprint_char('\n');
}