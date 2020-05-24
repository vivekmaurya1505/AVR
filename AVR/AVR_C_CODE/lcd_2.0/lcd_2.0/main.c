/*
 * lcd_2.0.c
 *
 * Created: 01-09-2019 07:50:45
 * Author : DESD
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <lcd.h>

int main(void)
{
	
	DDRC=0xff;
	lcd_init();
	char b[5];
	int a=10;
	lcd_result(a,b,10);
	lcd_string("abc");
	while (1)
	{
		
	PORTC=0x00;
	
		
	}
}


