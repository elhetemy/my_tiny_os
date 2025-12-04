global loader                   ; the entry symbol for ELF
extern kmain                    ; tell ASM that kmain exists in a C file

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes (4KB)

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; Point esp to the TOP of the stack
    
    call kmain                  ; Jump to our C code!

.loop:
    jmp .loop                   ; loop forever if kmain returns

section .bss                    ; Block Started by Symbol (uninitialized data)
align 4
kernel_stack:                   ; Label points to start of memory
    resb KERNEL_STACK_SIZE      ; Reserve 4KB of memory for the stack
