global load_idt
global interrupt_handler_33

extern interrupt_handler

; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
;        [esp    ] the return address
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; Defines a macro for an interrupt handler with NO error code
%macro no_error_code_interrupt_handler 1
interrupt_handler_%1:
    push dword 0                     ; push 0 as error code
    push dword %1                    ; push the interrupt number
    jmp common_interrupt_handler     ; jump to the common handler
%endmacro

common_interrupt_handler:
    ; save the registers
    push edi
    push esi
    push ebp
    push edx
    push ecx
    push ebx
    push eax

    ; call the C function
    call interrupt_handler

    ; restore the registers
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop ebp
    pop esi
    pop edi

    ; restore the esp (remove error code and ISR number)
    add esp, 8

    ; return to the code that got interrupted
    iret

; Create the handler for Interrupt 33 (Keyboard)
no_error_code_interrupt_handler 33
