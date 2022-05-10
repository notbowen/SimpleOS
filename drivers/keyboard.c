/* Handle Keyboard Inputs */
#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/utils.h"

// Called whenever IRQ1 occurs
static void keyboard_callback(registers_t regs) {
    // Scancode from keyboard is in 0x60
    u8 scancode = inb(0x60);
    char str_scancode[4];
    int_to_char(scancode, str_scancode);
    tprint("Scancode Received: ");
    tprint(str_scancode);
    tprint("\n");
}

// Init keyboard_callback to IRQ1
void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}