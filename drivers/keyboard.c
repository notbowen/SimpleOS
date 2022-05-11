/* Handle Keyboard Inputs */
#include "keyboard.h"
#include "ports.h"
#include "screen.h"

#include "../cpu/isr.h"

#include "../libc/mem.h"
#include "../libc/string.h"
#include "../libc/function.h"

#include "../kernel/kernel.h"

// Functions
void tprint_scancode(u8 scancode);

// Variables
#define BACKSPACE 0x0E
#define ENTER     0x1C

static char key_buffer[256];

// Character Array
#define SC_MAX    57
const char* sc_name[] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
    "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
    "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = { 
    '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

// Called whenever IRQ1 occurs
static void keyboard_callback(registers_t regs) {
    // Scancode from keyboard is in 0x60
    u8 scancode = inb(0x60);

    // Handle input
    if (scancode > SC_MAX) {
        return;
    }

    if (scancode == BACKSPACE) {
        // Move behind if there is still stuff in keybuffer (to prevent erasing terminal output)
        if (strlen(key_buffer) > 0) {
            tprint_backspace();
            back(key_buffer);
        }
        return;
    }

    if (scancode == ENTER) {
        tprint("\n");
        shell_input(key_buffer);
        key_buffer[0] = '\0';        // Reset keybuffer
        return;
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        tprint(str);
        return;
    }

    // Bypass unused param warning
    UNUSED(regs);
}

// Init keyboard_callback to IRQ1
void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}