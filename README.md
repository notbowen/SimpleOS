# SimpleOS
Simple OS, has `echo` and `snake`.

## About
This is a bare metal operating system that I made in hopes of having a deeper understanding of operating system fundamentals. It wasn't easy doing this project, and I faced many bugs. To make matters worse, there were limited resources on the internet, and I had trouble finding most of my issues. However, I have really learnt a lot from this project and it has indeed helped me understand operating systems better.

## Download and Run:
1. Download `os.iso`
2. Install `qemu` from [here](https://www.qemu.org/download/)
3. Run with `qemu_system_x86-64 -boot d -cdrom os.iso -m 512`


## Showcase
https://user-images.githubusercontent.com/85286288/173368881-c93ced3e-a604-4a5d-99aa-84b304b8965a.mp4


## Planned Features
✅ Print to screen

✅ Interactive shell

✅ Snek Game

:x: File System (Maybe?)

:x: Read/Write files?

## Bugs Encountered and how it was fixed
### 1. Printing not working correctly.
**Problem:**
Print function did not pass the strings correctly, and the strings did not show up in memory at times too, or showed up at far location. When char arrays with sizes > 7 are initialised, it would break and have incorrect values in it.

![image](https://user-images.githubusercontent.com/85286288/166937784-9c423862-2811-4b5a-8b26-778c32bae9de.png) 

**Fix:**
Turns out, I compiled the programs in 64 bits in an attempt to "fix" a linker error, which stated that the i386 format was not compatible with x86_64. This was resolved by compiling the programs in 32 bits using `-m32 -fno-pie` for gcc and `elf` for nasm, then linking with the option `-m elf_i386`.

![image](https://user-images.githubusercontent.com/85286288/166937887-2acca694-ad27-49a9-bf6f-15b44c6ec9a0.png)
![image](https://user-images.githubusercontent.com/85286288/166937914-f7a4d056-d467-4e49-a37f-a351b347941c.png)

(Got stuck on this for 1 week :/)

### 2. Keyboard inputs causing exception
**Problem:**
Even after fixing it, I am still not really sure what caused this problem, but after adding around 20 keyboard switch-cases, the system started calling interrupt 0x05, which is the Bound Range Exceeded interrupt.

![image](https://user-images.githubusercontent.com/85286288/167602756-e71897cf-6f51-4044-b81d-c29168de1d8c.png)

**Fix:**
For some reason, after adding `-nostdlib` and `-nodefaultlibs` to the linker command, the issue resolved itself. If I ever manage to figure out why it occured I'll come back and update this.

![image](https://user-images.githubusercontent.com/85286288/167602970-01fd4803-f7a2-4560-86c9-2834014c4d97.png)

### 3. Keyboard interrupts not happening in Snake Game
**Problem:**
Once the snake game was called, the keyboard interrupt request stopped working, so I couldn't receive keyboard inputs, while interrupt service routine continued to function normally.

**Fix:**
The keyboard interrupt request was not acknowledged, as the was I implemented it was to acknowledge it AFTER the game was finished, which resulted in the request not being acknowledged, and blocking other inputs too. I fixed it by acknowledging the keyboard interrupt before handling the interrupt, instead of after.

![image](https://user-images.githubusercontent.com/85286288/173329034-948c8905-8342-425a-a80f-a2e096c408f0.png)
![image](https://user-images.githubusercontent.com/85286288/173329081-d25a23de-464c-4487-89a6-4abde2e0f941.png)
