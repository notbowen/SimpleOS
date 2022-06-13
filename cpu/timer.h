#ifndef TIMER_H
#define TIMER_H

#include "../libc/typedefs.h"

void init_timer(u32 freq);
void sleep(u32 ticks);
u32 getCurrentTick();

#endif