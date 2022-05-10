# SimpleOS
Simple OS, does nothing.

## Planned Features
1. Print to screen
2. Interactive shell
3. Snek Game
4. File System (Maybe?)
5. Read/Write files?

## Bugs Encountered and how it was fixed
### 1. Printing not working correctly.
**Problem:**
Print function did not pass the strings correctly, and the strings did not show up in memory at times too, or showed up at far location. When char arrays with sizes > 7 are initialised, it would break and have incorrect values in it.

![image](https://user-images.githubusercontent.com/85286288/166937784-9c423862-2811-4b5a-8b26-778c32bae9de.png) 

**Fix:**
Turns out, I compiled the program in 64 bits in an attempt to "fix" a linker error, which stated that the i386 format was not compatible with x86_64. This was resolved by linking with the option `-m elf_i386`, and compiling C sources with the argument `-fno-pie`.

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
