#include <system.h>


/* Handles the keyboard interrupt */
static void keyboard_handler(registers_t* regs) {
	
	static const u16int Map[]={
		/* 00 */0,	0,	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',
		/* 10 */'9',	'0',	'-',	'=',	0,	0,	'q',	'w',	'e',	'r',
		/* 20 */'t',	'y',	'u',	'i',	'o',	'p',	'[',	']',	0,	0,
		/* 30 */'a',	's',	'd',	'f',	'g',	'h',	'j',	'k',	'l',	';',
		/* 40 */'\'',	'`',	0,	'\\',	'z',	'x',	'c',	'v',	'b',	'n',
		/* 50 */'m',	',',	'.',	'/',	0,	0,	0,	' ',	0,	0,
		/* 60 */0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		/* 70 */0,	'7',	'8',	'9',	0,	'4',	'5',	'6',	0,	'1',
		/* 80 */'2',	'3',	0,	0,	0,	0,	0,	0,	0,	0,
		/* 90 */0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		/* 100 */0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		
	};
	
	
	
	
	char code;
	int icode;
    code = inb(0x60);
	icode = code;
	if( icode > 0 ){
		kprintf("%c \n", Map[keycode[icode]]);
	}
	
	
   
     
}

void init_keyboard()
{
	fuc();
    register_interrupt_handler(IRQ1, &keyboard_handler);
	
}

void fuc(){
	static const unsigned short atkbd_unxlate_table[128] = {
		0,118, 22, 30, 38, 37, 46, 54, 61, 62, 70, 69, 78, 85,102, 13,
		21, 29, 36, 45, 44, 53, 60, 67, 68, 77, 84, 91, 90, 20, 28, 27,
		35, 43, 52, 51, 59, 66, 75, 76, 82, 14, 18, 93, 26, 34, 33, 42,
		50, 49, 58, 65, 73, 74, 89,124, 17, 41, 88, 5, 6, 4, 12, 3,
		11, 2, 10, 1, 9,119,126,108,117,125,123,107,115,116,121,105,
		114,122,112,113,127, 96, 97,120, 7, 15, 23, 31, 39, 47, 55, 63,
		71, 79, 86, 94, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 87,111,
		19, 25, 57, 81, 83, 92, 95, 98, 99,100,101,103,104,106,109,110
	};

	static unsigned char atkbd_set2_keycode[512] = {
		0, 67, 65, 63, 61, 59, 60, 88, 0, 68, 66, 64, 62, 15, 41,117,
		0, 56, 42, 93, 29, 16, 2, 0, 0, 0, 44, 31, 30, 17, 3, 0,
		0, 46, 45, 32, 18, 5, 4, 95, 0, 57, 47, 33, 20, 19, 6,183,
		0, 49, 48, 35, 34, 21, 7,184, 0, 0, 50, 36, 22, 8, 9,185,
		0, 51, 37, 23, 24, 11, 10, 0, 0, 52, 53, 38, 39, 25, 12, 0,
		0, 89, 40, 0, 26, 13, 0, 0, 58, 54, 28, 27, 0, 43, 0, 85,
		0, 86, 91, 90, 92, 0, 14, 94, 0, 79,124, 75, 71,121, 0, 0,
		82, 83, 80, 76, 77, 72, 1, 69, 87, 78, 81, 74, 55, 73, 70, 99,

		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		217,100,255, 0, 97,165, 0, 0,156, 0, 0, 0, 0, 0, 0,125,
		173,114, 0,113, 0, 0, 0,126,128, 0, 0,140, 0, 0, 0,127,
		159, 0,115, 0,164, 0, 0,116,158, 0,150,166, 0, 0, 0,142,
		157, 0, 0, 0, 0, 0, 0, 0,155, 0, 98, 0, 0,163, 0, 0,
		226, 0, 0, 0, 0, 0, 0, 0, 0,255, 96, 0, 0, 0,143, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,107, 0,105,102, 0, 0,112,
		110,111,108,112,106,103, 0,119, 0,118,109, 0, 99,104,119, 0,

		0, 0, 0, 65, 99,

	};
	
    int i,scancode;
    for (i = 0; i < 128; i++) {
        scancode = atkbd_unxlate_table[i];
        keycode[i] = atkbd_set2_keycode[scancode];
        keycode[i | 0x80] = atkbd_set2_keycode[scancode | 0x80];
    }
}
