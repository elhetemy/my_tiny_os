#include "keyboard.h"
#include "io.h"
#include "framebuffer.h"

#define KEYBOARD_DATA_PORT 0x60
#define BUFFER_SIZE 256

// CRITICAL FIX: 'volatile' tells the compiler these change unexpectedly!
volatile char key_buffer[BUFFER_SIZE];
volatile int write_ptr = 0;
volatile int read_ptr = 0;

u8int keyboard_read_scan_code() {
    return inb(KEYBOARD_DATA_PORT);
}

u8int keyboard_scan_code_to_ascii(u8int scan_code) {
    if (scan_code & 0x80) return 0; // Ignore releases

    switch(scan_code) {
        case 0x02: return '1'; case 0x03: return '2'; case 0x04: return '3';
        case 0x05: return '4'; case 0x06: return '5'; case 0x07: return '6';
        case 0x08: return '7'; case 0x09: return '8'; case 0x0A: return '9';
        case 0x0B: return '0'; case 0x0C: return '-'; case 0x0D: return '=';
        case 0x0E: return '\b'; 
        case 0x10: return 'q'; case 0x11: return 'w'; case 0x12: return 'e';
        case 0x13: return 'r'; case 0x14: return 't'; case 0x15: return 'y';
        case 0x16: return 'u'; case 0x17: return 'i'; case 0x18: return 'o';
        case 0x19: return 'p'; case 0x1A: return '['; case 0x1B: return ']';
        case 0x1C: return '\n'; // Enter
        case 0x1E: return 'a'; case 0x1F: return 's'; case 0x20: return 'd';
        case 0x21: return 'f'; case 0x22: return 'g'; case 0x23: return 'h';
        case 0x24: return 'j'; case 0x25: return 'k'; case 0x26: return 'l';
        case 0x27: return ';'; case 0x28: return '\''; case 0x29: return '`';
        case 0x2B: return '\\'; case 0x2C: return 'z'; case 0x2D: return 'x';
        case 0x2E: return 'c'; case 0x2F: return 'v'; case 0x30: return 'b';
        case 0x31: return 'n'; case 0x32: return 'm'; case 0x33: return ',';
        case 0x34: return '.'; case 0x35: return '/'; case 0x39: return ' ';
        default: return 0;
    }
}

void keyboard_handler_main() {
    u8int scancode = keyboard_read_scan_code();
    char ascii = keyboard_scan_code_to_ascii(scancode);

    if (ascii != 0) {
        // Echo to screen
        char str[2] = {ascii, '\0'};
        fb_write(str, 1);

        // Store in Buffer
        int next_write = (write_ptr + 1) % BUFFER_SIZE;
        if (next_write != read_ptr) {
            key_buffer[write_ptr] = ascii;
            write_ptr = next_write;
        }
    }
}

char keyboard_getc() {
    // This loop was getting stuck. 'volatile' fixes it.
    while (read_ptr == write_ptr) {
        // Wait...
    }

    char c = key_buffer[read_ptr];
    read_ptr = (read_ptr + 1) % BUFFER_SIZE;
    return c;
}

void keyboard_readline(char *buffer, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        char c = keyboard_getc();
        
        if (c == '\n') {
            break;
        }
        else if (c == '\b') {
            if (i > 0) i--;
        }
        else {
            buffer[i] = c;
            i++;
        }
    }
    buffer[i] = '\0';
}
