#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../libc/string.h"

void main() {
    clear_screen();
    isr_install();
    irq_install();

    tprint("SimpleOS v0.0.1\n");
    tprint("Type \"help\" for help.\n> ");
}

// End of shell output
void end_shell() {
    tprint("\n> ");
}

// TODO: Add a seperate folder dedicated to shell commands
void shell_input(char* input) {
    if (strcmp(input, "end") == 0) {
        tprint("Stopping CPU, Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(input, "") == 0 || isEmpty(input)) {
        tprint("> ");
        return;
    }

    char cmd[4];
    slice(input, cmd, 0, 3);

    // TODO: Tokenize commands and handle them that way
    if (strcmp(cmd, "echo") == 0) {
        char output[1024];
        slice(input, output, 5, strlen(input));
        tprint(output);
        end_shell();
        return;
    } 
    
    if (strcmp(cmd, "help") == 0) {
        tprint("===== HELP =====\n");
        tprint("1. echo {msg}: Prints {msg} to the screen.\n");
        tprint("2. cls: Clears the screen.\n");
        tprint("3. end: Halts the CPU.");
        end_shell();
        return;
    } 
    
    char cmd2[3];
    slice(input, cmd2, 0, 2);

    if (strcmp(cmd2, "cls") == 0) {
        clear_screen();
        tprint("> ");
        return;
    } else {
        tprint("Couldn't find command \"");
        tprint(input);
        tprint("\"!");
        end_shell();
        return;
    }
}