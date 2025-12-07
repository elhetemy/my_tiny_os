#include "interrupts.h"
#include "pic.h"
#include "io.h"
#include "framebuffer.h"
#include "keyboard.h"

#define INTERRUPTS_DESCRIPTOR_COUNT 256
#define INTERRUPTS_KEYBOARD 33

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

void interrupts_init_descriptor(s32int index, u32int address) {
    idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF;
    idt_descriptors[index].offset_low = (address & 0xFFFF);
    idt_descriptors[index].segment_selector = 0x08;
    idt_descriptors[index].reserved = 0x00;
    idt_descriptors[index].type_and_attr = 0x8E;
}

void interrupts_install_idt() {
    interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (u32int)interrupt_handler_33);

    idt.address = (s32int) &idt_descriptors;
    idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
    load_idt((s32int) &idt);

    pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
    
    // Disable Timer (IRQ0), Enable Keyboard (IRQ1)
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}

void interrupt_handler(struct cpu_state cpu, u32int interrupt, struct stack_state stack) {
    
    if (interrupt == INTERRUPTS_KEYBOARD) {
        // CRITICAL: Call the main keyboard driver logic!
        keyboard_handler_main();
        
        pic_acknowledge(interrupt);
    }
}
