; Writes to vid buffer to print to screen
[bits 32]
VIDEO_MEMORY equ 0xb8000   ; vid buffer location
WHITE_ON_BLACK equ 0x0F

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx]  ; [ebx] is where char is stored
    mov ah, WHITE_ON_BLACK

    cmp al, 0      ; Check if end
    je print_string_pm_done

    mov [edx], ax
    add ebx, 1     ; Next char
    add edx, 2     ; Next vid mem pos

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret