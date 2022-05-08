#include "keyboard.h"
#include "ports.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../libc/utils.h"

void print_letter(u8 scancode);

static void keyboard_callback(registers_t reg) {
    u8 scancode = inb(0x60);  // Keyboard scancode is at 0x60
    char sc_str[255];
    int_to_char(scancode, sc_str);
    tprint("Keyboard Scancode: ");
    tprint(sc_str);
    tprint(", ");
    print_letter(scancode);
    tprint("\n");
}

void init_keyboard() {
    // Install IRQ Handler
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void print_letter(u8 scancode) {
    switch (scancode) {
        case 0x0:
            tprint("ERROR");
            break;
        case 0x1:
            tprint("ESC");
            break;
        case 0x2:
            tprint("1");
            break;
        case 0x3:
            tprint("2");
            break;
        case 0x4:
            tprint("3");
            break;
        case 0x5:
            tprint("4");
            break;
        case 0x6:
            tprint("5");
            break;
        case 0x7:
            tprint("6");
            break;
        case 0x8:
            tprint("7");
            break;
        case 0x9:
            tprint("8");
            break;
        case 0x0A:
            tprint("9");
            break;
        case 0x0B:
            tprint("0");
            break;
        case 0x0C:
            tprint("-");
            break;
        case 0x0D:
            tprint("+");
            break;
        case 0x0E:
            tprint("Backspace");
            break;
        case 0x0F:
            tprint("Tab");
            break;
        case 0x10:
            tprint("Q");
            break;
        case 0x11:
            tprint("W");
            break;
        case 0x12:
            tprint("E");
            break;
        case 0x13:
            tprint("R");
            break;
        case 0x14:
            tprint("T");
            break;
        case 0x15:
            tprint("Y");
            break;
        case 0x16:
            tprint("U");
            break;
        case 0x17:
            tprint("I");
            break;
        case 0x18:
            tprint("O");
            break;
        case 0x19:
            tprint("P");
            break;
        case 0x1A:
			tprint("[");
			break;
		case 0x1B:
			tprint("]");
			break;
		case 0x1C:
			tprint("ENTER");
			break;
		case 0x1D:
			tprint("LCtrl");
			break;
		case 0x1E:
			tprint("A");
			break;
		case 0x1F:
			tprint("S");
			break;
        case 0x20:
            tprint("D");
            break;
        case 0x21:
            tprint("F");
            break;
        case 0x22:
            tprint("G");
            break;
        case 0x23:
            tprint("H");
            break;
        case 0x24:
            tprint("J");
            break;
        case 0x25:
            tprint("K");
            break;
        case 0x26:
            tprint("L");
            break;
        case 0x27:
            tprint(";");
            break;
        case 0x28:
            tprint("'");
            break;
        case 0x29:
            tprint("`");
            break;
        case 0x2A:
			tprint("LShift");
			break;
		case 0x2B:
			tprint("\\");
			break;
		case 0x2C:
			tprint("Z");
			break;
		case 0x2D:
			tprint("X");
			break;
		case 0x2E:
			tprint("C");
			break;
		case 0x2F:
			tprint("V");
			break;
        case 0x30:
            tprint("B");
            break;
        case 0x31:
            tprint("N");
            break;
        case 0x32:
            tprint("M");
            break;
        case 0x33:
            tprint(",");
            break;
        case 0x34:
            tprint(".");
            break;
        case 0x35:
            tprint("/");
            break;
        case 0x36:
            tprint("Rshift");
            break;
        case 0x37:
            tprint("Keypad *");
            break;
        case 0x38:
            tprint("LAlt");
            break;
        case 0x39:
            tprint("Spc");
            break;

        default:
            if (scancode <= 0x7F) {
                tprint("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                print_letter(scancode - 0x80);
                tprint(" key up");
            } else {
                tprint("Unknown key up");
            }
            break;
    }
}