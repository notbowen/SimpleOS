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
Problem:

Print function did not pass the strings correctly, and the strings did not show up in memory at times too, or showed up at far location. When char arrays with sizes > 7 are initialised, it would break and have incorrect values in it.

Fix:

Turns out, I compiled the program in 64 bits in an attempt to override a linker error, which stated that the i386 format was not compatible with x86_64. This was resolved by linking with the option -m elf_i386, and compiling C sources with the argument -fno-pie.

(Got stuck on this for 1 week :/)