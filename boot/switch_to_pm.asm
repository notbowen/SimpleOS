; Switches from 16 bit real mode to 32 bit protected mode
[bits 16]
switch_to_pm:
    cli                   ; Disable interrupts
    lgdt [gdt_descriptor] ; Load GDT
    mov eax, cr0          ; Flip 32-bit mode bit in CPU
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG  ; Point everything to DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 

    mov ebp, 0x90000  ; Update stack
    mov esp, ebp

    call BEGIN_PM