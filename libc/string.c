/* File to store all string related functions */
#include "string.h"

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

// Appends to char array
void append(char arr[], char c) {
    int len = strlen(arr);
    arr[len] = c;
    arr[len+1] = '\0';
}

// Removes end of char array
void back(char arr[]) {
    int len = strlen(arr);
    arr[len-1] = '\0';
}

// Slices string from start to end
void slice(char str[], char out[], int start, int end) {
    int j = 0;
    for (int i = start; i <= end; i++) {
        out[j++] = str[i];
    }
    out[j] = '\0';
}

// Get length of string
int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}

// Compares if strings are equal, returns 0 if yes
// Returns -ve if s1<s2, returns +ve if s1>s2
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') {
            return 0;
        }
    }

    return s1[i] - s2[i];
}