#include "../drivers/framebuffer.h"
#include "../drivers/interrupts.h"
#include "../drivers/keyboard.h"
#include "utils.h"

void enable_hardware_interrupts();

void kmain() {
    // 1. Setup
    fb_clear();
    interrupts_install_idt();
    enable_hardware_interrupts();

    // 2. Welcome Message (Using strlen to be safe!)
    char *msg1 = "Welcome to MyOS Shell!\n";
    fb_write(msg1, strlen(msg1));
    
    char *msg2 = "Type 'help' for commands.\n";
    fb_write(msg2, strlen(msg2));

    char buffer[256];

    // 3. The Shell Loop
    while(1) {
        // Print Prompt
        fb_write("\nmyos> ", 7);

        // Wait for input
        keyboard_readline(buffer, 256);

        // Check Commands
        if (strcmp(buffer, "clear") == 0) {
            fb_clear();
            fb_write(msg1, strlen(msg1));
        }
        else if (strcmp(buffer, "help") == 0) {
            char *help_msg = "\nAvailable Commands:\n"
                             "  help    - Show this message\n"
                             "  clear   - Clear screen\n"
                             "  echo    - Repeat text\n"
                             "  version - Show version\n";
            fb_write(help_msg, strlen(help_msg));
        }
        else if (strcmp(buffer, "version") == 0) {
            char *ver = "\nMyOS v1.0 - Built for UWE Worksheet 2\n";
            fb_write(ver, strlen(ver));
        }
        // Handle "echo" (Starts with "echo ")
        else if (buffer[0] == 'e' && buffer[1] == 'c' && buffer[2] == 'h' && buffer[3] == 'o' && buffer[4] == ' ') {
            fb_write("\n", 1);
            fb_write(buffer + 5, strlen(buffer) - 5); // Skip "echo "
            fb_write("\n", 1);
        }
        // Handle empty enter key
        else if (buffer[0] == '\0') {
            // Do nothing
        }
        else {
            fb_write("\nUnknown command: ", 18);
            fb_write(buffer, strlen(buffer));
            fb_write("\n", 1);
        }
    }
}
