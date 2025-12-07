#include "utils.h"

// Returns 0 if strings are identical
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

// Returns the length of a string
int strlen(char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        i++;
    }
    return i;
}
