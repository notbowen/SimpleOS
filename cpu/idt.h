/* Interrupt Descriptor Table Header */
/* Defines how each interrupt data is stored */

#ifndef IDT_H
#define IDT_H

#include "../libc/typedefs.h"

#define KERNEL_CS 0x08

// IDT Gate
typedef struct {
    u16 low_offset;         // Lower 16 bit addr to jump to when interrupt occurs
    u16 sel;                // Kernel segment selector
    u8 always0;

    u8 flags;
    u16 high_offset;       // Upper 16 bits of addr to jump to
} __attribute__((packed)) idt_gate_t;

// Pointer to arr of interrupt handlers
typedef struct {
    u16 limit;
    u32 base;               // First element of idt_gate_t array
} __attribute__((packed)) idt_register_t;

// Setup IDT
#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

// idt.c global functions
void set_idt_gate(int n, u32 handler);
void set_idt();

#endif