/* Uses the PIT to see how much time has elapsed */
#include "timer.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;

    // Bypass unused param warning
    UNUSED(regs);
}

// Sleep for given ticks
void sleep(u32 ticks) {
    u32 endingTick = tick + ticks;

    while (tick < endingTick) {
        // PASS
    }

    return;
}

// Get current tick
u32 getCurrentTick() {
    return tick;
}

// Initialises timer at specified frequency
void init_timer(u32 freq) {
    // Register/Install the function
    register_interrupt_handler(IRQ0, timer_callback);

    // Get PIT Value
    u32 divisor = 1193180 / freq;
    u8 low = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);

    // Send to port
    outb(0x43, 0x36);
    outb(0x40, low);
    outb(0x40, high);
}