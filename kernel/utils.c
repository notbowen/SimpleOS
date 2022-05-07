/* File to store all frequently used functions */
#include "utils.h"

// Copies the data from src to dest
void memory_copy(char* src, char* dest, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        *(dest + i) = *(src + i);
    }
}

// Converts from int to char to be printed out
// Modifies caller defined char array
void int_to_char(int num, char arr[]) {
    int i, sign;
    if ((sign = num) < 0) num = -num; // Make number +ve
    i = 0;
    do {                              // Keep dividing by 10 and convert remainder to char
        arr[i++] = num % 10 + '0';    // And append the char
    } while ((num /= 10) > 0);

    if (sign < 0) arr[i++] = '-';     // Add -ve sign back again
    arr[i] = '\0';                    // Null terminate string

    // Reverse string as the above code outputs number in descending order
    reverse(arr);
}

// Reverses a string array
void reverse(char str[]) {
    // Swaps first & last, 2nd and 2nd last, 3rd and 3rd last and so on
    for (int i = 0, j = strlen(str) - 1; i < j; i++, j--) { 
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

// Get length of string
int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}