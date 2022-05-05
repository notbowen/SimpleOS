; Uses BIOS 0x10 interrupt to print to screen
print:
    pusha

start:
    mov al, [bx]  ; bx is the base addr of string
    cmp al, 0     ; Check if reached end of str
    je done

    mov ah, 0x0e  ; BIOS TTY Mode
    int 0x10

    ; Increment pos
    add bx, 1
    jmp start

done:
    ; Print new line
    mov ah, 0x0e
    mov al, 0x0a  ; \n
    int 0x10

    mov al, 0x0d  ; \r
    int 0x10

    popa
    ret