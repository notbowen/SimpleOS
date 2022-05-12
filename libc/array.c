/* Array related operations */
#include "array.h"
#include "string.h"

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