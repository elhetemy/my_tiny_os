OBJECTS = loader.o kmain.o source/io.o drivers/pic.o drivers/framebuffer.o drivers/interrupts.o drivers/interrupt_handlers.o drivers/hardware_interrupt_enabler.o drivers/keyboard.o source/utils.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T source/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

loader.o: source/loader.asm
	nasm -f elf source/loader.asm -o loader.o

source/io.o: source/io.asm
	nasm -f elf source/io.asm -o source/io.o

drivers/pic.o: drivers/pic.c
	$(CC) $(CFLAGS) drivers/pic.c -o drivers/pic.o





kmain.o: source/kmain.c
	$(CC) $(CFLAGS) source/kmain.c -o kmain.o

drivers/framebuffer.o: drivers/framebuffer.c
	$(CC) $(CFLAGS) drivers/framebuffer.c -o drivers/framebuffer.o

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o iso/boot/kernel.elf

os.iso: kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

run: os.iso
	qemu-system-i386 -display curses -monitor telnet::45454,server,nowait -serial mon:stdio -boot d -cdrom os.iso -m 32 -d cpu -D logQ.txt

clean:
	rm -f *.o drivers/*.o iso/boot/kernel.elf os.iso logQ.txt


drivers/interrupts.o: drivers/interrupts.c
	$(CC) $(CFLAGS) drivers/interrupts.c -o drivers/interrupts.o

drivers/interrupt_handlers.o: drivers/interrupt_handlers.asm
	nasm -f elf drivers/interrupt_handlers.asm -o drivers/interrupt_handlers.o

drivers/hardware_interrupt_enabler.o: drivers/hardware_interrupt_enabler.asm
	nasm -f elf drivers/hardware_interrupt_enabler.asm -o drivers/hardware_interrupt_enabler.o


drivers/keyboard.o: drivers/keyboard.c
	$(CC) $(CFLAGS) drivers/keyboard.c -o drivers/keyboard.o


source/utils.o: source/utils.c
	$(CC) $(CFLAGS) source/utils.c -o source/utils.o
