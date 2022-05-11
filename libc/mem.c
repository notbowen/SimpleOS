/* File to store all memory related functions */
#include "mem.h"

// Copies the data from src to dest
void memory_copy(char* src, char* dest, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        *(dest + i) = *(src + i);
    }
}