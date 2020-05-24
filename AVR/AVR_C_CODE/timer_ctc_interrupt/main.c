/*
 * timer_ctc_interrupt.c
 *
 * Created: 04-09-2019 14:12:26
 * Author : DESD
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
void timer1_init();

int main(void)
{
	DDRC=0xff;
	timer1_init();                             
	while (1){                                     
	}
}
void timer1_init(){
	sei();
	TIMSK|=(1<<OCIE1A);
	TCNT1=0;
	OCR1A=15624;
	TCCR1B|=(1<<CS10)|(1<<WGM12)|(1<<CS12);
	
}
ISR(TIMER1_COMPA_vect){
	PORTC=~(PORTC);  
	
}