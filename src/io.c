//This program is licensed under the GPLv3; see COPYING for more info.
//Copyright 2008 Sprite_tm

#include "io.h"
#include <avr/io.h>
#include <util/delay.h>

#define PSTR PD6 //-strobe
#define PACK PD5 //ack; not used
#define PBSY PD4 //-busy
//portb is used fully as data out (d0-7)

void initio(void)
{
    //Init I/O
    DDRB = 0xff; //make data port output
    DDRD = _BV(PSTR);
    PORTD = _BV(PACK) | _BV(PBSY) | _BV(PSTR); //pull-ups
}


void sendbyte(char data)
{
    //Set data
    PORTB = data;

    //Wait until printer isn't busy anymore
    while (PIND & _BV(PBSY)) ;

    //Pulse strobe
    _delay_ms(1);
    PORTD &= ~_BV(PSTR);
    _delay_ms(1);
    PORTD |= _BV(PSTR);
    _delay_ms(1);
}
