#include "../drivers/screen.h"
#include "../kernel/utils.h"

void main() {
    clear_screen();

    for (int i = 0; i < (MAX_ROWS + 5); i++) {
        char output[255];
        tprint("Line ");
        int_to_char(i, output);
        tprint(output);
        tprint("\n");
    }
}