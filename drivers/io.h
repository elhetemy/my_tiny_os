#ifndef IO_H
#define IO_H

/**
 * outb:
 * Sends a byte to an I/O port.
 * Used for moving the cursor.
 */
static inline void outb(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" : : "a"(data), "nd"(port));
}

#endif
