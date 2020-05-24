/*
 * led1.c.c
 *
 * Created: 31-08-2019 09:50:34
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRC=0XFF;             //set direction PORTA as a output
    while (1)               // infinite loop
    {
		
		PORTC=0xaa;        
	    _delay_ms(500);    // set delay for 0.5 sec
		PORTC=0x50;
	    _delay_ms(500);    // set delay for 0.5 sec
		PORTC=0xff;
    }
}

