#include "pic.h"

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
#define ICW1_ICW4       0x01        /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08        /* Level triggered (edge) mode */
#define ICW1_INIT       0x10        /* Initialization - required! */

#define ICW4_8086       0x01        /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02        /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08        /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C        /* Buffered mode/master */
#define ICW4_SFNM       0x10        /* Special fully nested (not) */

void pic_remap(s32int offset1, s32int offset2)
{
    unsigned char a1, a2;

    a1 = inb(PIC_1_DATA_PORT);                        // save masks
    a2 = inb(PIC_2_DATA_PORT);

    outb(PIC_1_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
    outb(PIC_2_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
    outb(PIC_1_DATA_PORT, offset1);                 // ICW2: Master PIC vector offset
    outb(PIC_2_DATA_PORT, offset2);                 // ICW2: Slave PIC vector offset
    outb(PIC_1_DATA_PORT, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC_2_DATA_PORT, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

    outb(PIC_1_DATA_PORT, ICW4_8086);
    outb(PIC_2_DATA_PORT, ICW4_8086);

    outb(PIC_1_DATA_PORT, a1);   // restore saved masks.
    outb(PIC_2_DATA_PORT, a2);
}

void pic_acknowledge(u32int interrupt) {
    if (interrupt >= 40) {
        outb(PIC_2_COMMAND_PORT, PIC_ACKNOWLEDGE);
    }
    outb(PIC_1_COMMAND_PORT, PIC_ACKNOWLEDGE);
}
