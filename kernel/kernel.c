#include "../drivers/screen.h"
#include "../libc/utils.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main() {
    clear_screen();
    isr_install();

    // Test interrupt
    asm volatile ("int $2");    
    asm volatile ("int $3");
}