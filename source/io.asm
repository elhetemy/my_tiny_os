global outb
global inb

; outb - Sends a byte to an I/O port
; stack: [esp + 8] data
;        [esp + 4] port
;        [esp    ] return address
outb:
    mov al, [esp + 8]    ; move the data to al
    mov dx, [esp + 4]    ; move the port to dx
    out dx, al           ; write the data to the port
    ret

; inb - returns a byte from the given I/O port
; stack: [esp + 4] port
;        [esp    ] return address
inb:
    mov dx, [esp + 4]    ; move the port to dx
    in al, dx            ; read a byte from port to al
    ret
