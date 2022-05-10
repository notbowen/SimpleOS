C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h cpu/*.h)

OBJ = $(C_SOURCES:.c=.o cpu/interrupt.o)

C_FLAGS = -ggdb -ffreestanding -Wall -Wextra -fno-exceptions -fno-pie -m32
# -Werror

os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -nostdlib -nodefaultlibs -m elf_i386 -s -o $@ -Ttext 0x1000 $^ --oformat binary -entry main

# For debugging
kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -nostdlib -nodefaultlibs -m elf_i386 -s -o $@ -Ttext 0x1000 $^ -entry main

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -fda os-image.bin -d guest_errors,int -gdb tcp::1234 -S

%.o: %.c ${HEADERS}
	gcc $(C_FLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o