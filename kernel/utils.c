/* File to store all frequently used functions */
void memory_copy(char* src, char* dest, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        *(dest + i) = *(src + i);
    }
}