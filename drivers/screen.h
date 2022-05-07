/* Header Guards */
#ifndef SCREEN_H
#define SCREEN_H

/* The I/O ports */
#define CMD_PORT        0x3D4
#define DATA_PORT       0x3D5

/* The I/O port commands */
#define HIGH_BYTE       14
#define LOW_BYTE        15

/* Video Stuff */
#define VIDEO_MEMORY    0x000B8000 
#define MAX_ROWS        25
#define MAX_COLS        80

/* Colors */
#define BLACK_ON_WHITE  0x0F

/* Public Functions */
void clear_screen();
void tprint_char(char c);
void tprint(char str[]);

#endif