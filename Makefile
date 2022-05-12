C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h cpu/*.h)

OBJ = $(C_SOURCES:.c=.o cpu/interrupt.o)

C_FLAGS = -ggdb -ffreestanding -Wall -Wextra -fno-exceptions -fno-pie -m32
# -Werror

os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -nostdlib -nodefaultlibs -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary -entry main

# For debugging
kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -nostdlib -nodefaultlibs -m elf_i386 -o $@ -Ttext 0x1000 $^ -entry main

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -fda os-image.bin -gdb tcp::1234 -S

img: os-image.bin os.img
	cp os.img iso/
	genisoimage -quiet -V 'SimpleOS' -input-charset iso8859-1 -o os.iso -b os.img -hide os.img iso/

os.img: os-image.bin
	dd if=/dev/zero of=os.img bs=1024 count=1440
	dd if=boot/boot.bin of=os.img seek=0 count=1 conv=notrunc
	dd if=kernel.bin of=os.img seek=1 count=256 conv=notrunc

%.o: %.c ${HEADERS}
	gcc $(C_FLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf os-image.bin
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
	rm -rf *.img iso/*.img