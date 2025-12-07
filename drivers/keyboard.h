#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

#include "types.h"

// The Interrupt Handler calls this
void keyboard_handler_main();

// User functions
char keyboard_getc();
void keyboard_readline(char *buffer, int max_len);

#endif
