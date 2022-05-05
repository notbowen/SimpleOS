[org 0x7c00]
KERNEL_OFFSET equ 0x1000  ; Define where the kernel is

    mov [BOOT_DRIVE], dl  ; BIOS sets dl to the boot drive (might be overwritten ltr, so we save)
    mov bp, 0x9000        ; Set stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    
    call load_kernel      ; Load kernel from disk
    call switch_to_pm     ; Switch to 32 bit Protected Mode
    jmp $

; Include Files
%include "boot/print.asm"
%include "boot/print_hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/print32.asm"
%include "boot/switch_to_pm.asm"

; Load kernel in Real Mode
[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print

    mov bx, KERNEL_OFFSET  ; Read from disk and store info at KERNEL_OFFSET
    mov dh, 16             ; Read 16 sectors
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

; 32 bit init jumps here
; Call kernel
[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET     ; Start kernel
    jmp $                  ; Shldn't come back here but just in case

; Variables
BOOT_DRIVE      db 0
MSG_REAL_MODE   db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE   db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel...", 0

; Bootsect Padding
times 510-($-$$) db 0
dw 0xaa55