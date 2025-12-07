#include "io.h"
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

char *fb = (char *) 0x000B8000;

unsigned short cursor_x = 0;
unsigned short cursor_y = 0;

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move(unsigned short x, unsigned short y) {
    cursor_x = x;
    cursor_y = y;
    unsigned short pos = y * 80 + x;
    fb_move_cursor(pos);
}

void fb_write(char *buf, unsigned int len) {
    unsigned int i;
    for (i = 0; i < len; i++) {
        
        // Handle Backspace
        if (buf[i] == '\b') {
            if (cursor_x > 0) {
                cursor_x--; // Move cursor back
                // Overwrite old char with space
                unsigned int pos = cursor_y * 80 + cursor_x;
                fb_write_cell(pos, ' ', 0, 7); 
            }
        }
        // Handle Newline (Enter key)
        else if (buf[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        }
        // Handle Normal Characters
        else {
            unsigned int pos = cursor_y * 80 + cursor_x;
            fb_write_cell(pos, buf[i], 0, 7);
            
            cursor_x++;
            if (cursor_x >= 80) {
                cursor_x = 0;
                cursor_y++;
            }
        }
    }
    // Update the hardware cursor to match
    fb_move_cursor(cursor_y * 80 + cursor_x);
}

void fb_clear() {
    unsigned int i;
    for (i = 0; i < 80 * 25; i++) {
        fb_write_cell(i, ' ', 0, 7);
    }
    cursor_x = 0;
    cursor_y = 0;
    fb_move_cursor(0);
}
