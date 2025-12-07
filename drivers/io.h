#ifndef IO_H
#define IO_H

/* We are now using external ASM functions */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif
