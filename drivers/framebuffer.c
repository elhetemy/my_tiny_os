#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

/* Video memory starts at this address */
char *fb = (char *) 0x000B8000;

/**
 * fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position.
 * pos is a linear index (row * 80 + col).
 */
void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

/**
 * fb_write_cell:
 * Writes a character with the given foreground and background to position i.
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/**
 * fb_move:
 * Moves the cursor to x, y (Requested by PDF Task 3).
 * Screen is 80 chars wide.
 */
void fb_move(unsigned short x, unsigned short y) {
    unsigned short pos = y * 80 + x;
    fb_move_cursor(pos);
}

/**
 * fb_write:
 * Writes a string to the buffer at the current cursor location.
 * (Simplified for this task: writes to the start of the screen).
 */
void fb_write(char *buf, unsigned int len) {
    unsigned int i;
    for (i = 0; i < len; i++) {
        // Write char in Light Grey (7) on Black (0)
        fb_write_cell(i, buf[i], 0, 7); 
    }
    fb_move_cursor(len); // Move cursor to end of string
}
/**
 * fb_clear:
 * Clears the entire screen by writing spaces (ASCII 32)
 * with a black background and light grey text.
 */
void fb_clear() {
    unsigned int i;
    // The screen is 80 columns * 25 rows = 2000 characters
    for (i = 0; i < 80 * 25; i++) {
        fb_write_cell(i, ' ', 0, 7);
    }
    fb_move_cursor(0); // Move cursor back to top-left
}
