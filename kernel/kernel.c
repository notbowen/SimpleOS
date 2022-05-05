#include "../drivers/screen.h"

void main() {
    unsigned char* v_mem = (unsigned char*) VIDEO_MEMORY;

    v_mem[0] = '0';
    v_mem[2] = '2';
    v_mem[4] = '4';
}