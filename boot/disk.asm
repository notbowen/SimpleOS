; Load dh sectors from drve dl
disk_load:
    pusha

    push dx

    mov ah, 0x02  ; BIOS read paramenter, 0x02 = read
    mov al, dh    ; No. of sectors, alr defined when called 
    mov cl, 0x02  ; Sector
    mov ch, 0x00   ; Cylinder
    mov dh, 0x00  ; Head number

    int 0x13      ; BIOS Disk Interrupt
    jc disk_error ; If carry bit set, error occured

    pop dx
    cmp al, dh    ; Check if correct sectors read
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, MSG_DISK_ERROR
    call print

    mov dh, ah  ; ah -> error code
    call print_hex
    jmp $

sectors_error:
    mov bx, MSG_SECTORS_ERROR
    call print

    jmp $

; Variables
MSG_DISK_ERROR:    db "Disk read error!", 0
MSG_SECTORS_ERROR: db "Incorrect no. of sectors read!", 0