//This program is licensed under the GPLv3; see license.txt for more info.
//Copyright 2008 Sprite_tm

#include "io.h"
#include "avr/interrupt.h"
#include "avr/pgmspace.h"
#include "util/delay.h"

//PJL string to send something to the display. The data sent in between the
//'pre' and 'post' is displayed on the HPLJs display.
const char pre[] PROGMEM = "\033%-12345X@PJL RDYMSG DISPLAY = \"";
const char post[] PROGMEM = "\"\r\n\033%-12345X\r\n";

//Messages
#define NO_OF_MESSAGES 18
const char messages[NO_OF_MESSAGES][17] PROGMEM = {
    "ben ik al opge- ",
    "ruimd? En nu dan",
    "? Owww, ik sta  ",
    "hier best irri- ",
    "tant in de weg, ",
    "is mij verteld. ",
    "Mag ik nou op   ",
    "Roy z'n kamer   ",
    "alstjeblieft?   ",
    "Ik zal niet     ",
    "tegen de bank   ",
    "aanpissen en al-",
    "tijd heel aardig",
    "voor je zijn en ",
    "nergens toner   ",
    "achterlaten. En ",
    "ik blijf me toch",
    "afvragen: Oww,  "
};

//Simple routine to print the zero-terminated string 'data' which should be located
//in program memory.
void printstr(const char *data)
{
    char d;
    do {
        d = pgm_read_byte(data++);
        if (d != 0) sendbyte(d);
    } while (d != 0);
}

//Main routine
int main(void)
{
    int x;
    int msg = 0;
    //Init I/O
    initio();
    while (1) {
        //Print pre, post, message
        printstr(pre);
        printstr(messages[msg]);
        printstr(post);
        //Take the next message; wrap to 0 if we had the last
        msg++; if (msg >= NO_OF_MESSAGES) msg = 0;

        //Delay 2 seconds.
        for (x = 0; x < 100; x++) _delay_ms(20);
    }
}
