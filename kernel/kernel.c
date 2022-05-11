#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"

void main() {
    clear_screen();
    isr_install();
    irq_install();

    tprint("SimpleOS v0.0.1\n> ");
}

// TODO: Add a seperate folder dedicated to shell commands
void shell_input(char* input) {
    if (strcmp(input, "END") == 0) {
        tprint("Stopping CPU, Bye!\n");
        asm volatile("hlt");
    }

    char cmd[4];
    slice(input, cmd, 0, 3);
    if (strcmp(cmd, "ECHO") == 0) {
        char output[256];
        slice(input, output, 5, strlen(input));
        tprint(output);
    } else if (strcmp(cmd, "HELP") == 0) {
        tprint("===== HELP =====\n");
        tprint("1. ECHO {MSG}: PRINTS {MSG} TO SCREEN\n");
        tprint("2. END: STOPS THE CPU");
    } 

    else {
        tprint("Couldn't find command \"");
        tprint(input);
        tprint("\"!");
    }

    tprint("\n> ");
}