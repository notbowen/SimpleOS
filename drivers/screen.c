/*
Notes: 
1. Conversion from pos to actual index: (pos*2) + 1 
   - Pos starts from 0
2. index: character data, index + 1: color data
*/

#include "ports.h"
#include "screen.h"

#define uint16_t unsigned short

/* Function Decleration */
void move_cursor(unsigned short pos);
uint16_t getPos(uint16_t row, uint16_t col);
uint16_t getIndex(uint16_t pos);
uint16_t get_cursor();

/* Public Functions */

// Clears the screen
// Usage: clear_screen()
void clear_screen() {
    // LETS GO IT WORKS :OOOOO
    unsigned char* v_mem = (unsigned char*) VIDEO_MEMORY;

    for (uint16_t row = 0; row < MAX_ROWS; row++) {
        for (uint16_t col = 0; col < MAX_COLS; col++) {
            uint16_t index = getIndex(getPos(row, col));
            v_mem[index] = ' ';
            v_mem[++index]= BLACK_ON_WHITE;  // Index + 1 doesn't work, ++ works dk why
        }
    }

    move_cursor(0);
}

// Prints a char at a given row and col
// Usage: tprint_char(char)
void tprint_char(char c) {
    // Calculate pos and index
    uint16_t pos = get_cursor();
    uint16_t index = getIndex(pos);

    // Get vidmem
    unsigned char* v_mem = (unsigned char*) VIDEO_MEMORY;

    // Handle \n
    switch (c) {
        case '\n':
            // Move down 1 row
            pos += MAX_COLS;
            // Move to start of row
            pos -= (pos % MAX_COLS);

            break;
    
        default:
            // Write to vid mem
            v_mem[index] = c;
            v_mem[++index] = BLACK_ON_WHITE;

            pos++;
            break;
    }

    // Handle overflow
    if (pos >= MAX_ROWS * MAX_COLS) {
        pos = 0;  // TODO: Handle scrolling
    }

    // Update cursor position
    move_cursor(pos);
}

// Prints a string at current cursor location
void tprint(char msg[]) {
    msg++;

    while (*msg) {
        tprint_char(*msg);
        msg++;
    }
}

/* Private Functions */
// Moves cursor to specified pos
void move_cursor(uint16_t pos) {
    outb(CMD_PORT, HIGH_BYTE);
    outb(DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(CMD_PORT, LOW_BYTE);
    outb(DATA_PORT, pos & 0x00FF);
}

// Returns the pos of cursor
uint16_t get_cursor() {
    outb(CMD_PORT, HIGH_BYTE);
    uint16_t pos = inb(DATA_PORT) << 8;
    outb(CMD_PORT, LOW_BYTE);
    pos += inb(DATA_PORT);

    return pos;
}

// Gets the raw memory index from pos
uint16_t getIndex(uint16_t pos) {
    return (pos * 2) + 1;
}

uint16_t getPos(uint16_t row, uint16_t col) {
    return (row * MAX_COLS) + col;
}