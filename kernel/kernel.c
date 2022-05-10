#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
    clear_screen();
    isr_install();

    asm volatile("sti");  // Enable interrupts

    init_timer(50);
    init_keyboard();
}