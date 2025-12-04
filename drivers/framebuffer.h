#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

void fb_write(char *buf, unsigned int len);
void fb_move(unsigned short x, unsigned short y);
void fb_clear();  // <--- Added this

#endif
