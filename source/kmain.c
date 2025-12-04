#include "../drivers/framebuffer.h"

/* The function required by the book/assignment */
int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

/* Extra function */
int multiply_two(int a, int b) {
    return a * b;
}

void kmain() {
    // 1. Test Math
    sum_of_three(1, 2, 3);
    multiply_two(10, 5);

    // 2. Clear the screen first! (Removes the GRUB text)
    fb_clear();

    // 3. Print Hello World
    char welcome_msg[] = "Hello World!";
    fb_write(welcome_msg, 12);
    
    // 4. Move cursor
    fb_move(0, 1);
    
    while(1) {}
}
