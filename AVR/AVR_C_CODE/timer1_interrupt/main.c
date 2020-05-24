/*
 * timer1_interrupt.c
 *
 * Created: 04-09-2019 07:46:56
 * Author : DESD
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <lcd.h>
void timer1_init();



int main(void)
{
	DDRC=0XFF;
	lcd_init();
	timer1_init();
	while (1)
	{
		
	}
}
void timer1_init(){
	sei();
	TIMSK|=(1<<TOIE1);
	TCNT1=49536;
	TCCR1B|=(1<<CS10)|(1<<CS12);    //   1024
}
ISR(TIMER1_OVF_vect){
	
	
	PORTC =~PORTC;
	lcd_string("bcd");
	TCNT1=49536;
	
}
