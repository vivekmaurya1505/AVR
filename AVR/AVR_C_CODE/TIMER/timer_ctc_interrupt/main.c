/*
 * timer_ctc_interrupt.c
 *
 * Created: 04-09-2019 14:12:26
 * Author :  PRN 19084013020111,PRN 19084013020112 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
void timer1_init();

int main(void)
{ //set direction port c as a output for led
	DDRC=0xff;                                       
	timer1_init();                                  //timer1 initialization                        
	while (1){                                      //infinite loop        
	}
}
void timer1_init(){              
	sei();
	TIMSK|=(1<<OCIE1A);                           //Enabling interrupt 
	TCNT1=0;                   
	OCR1A=15624;                                  //setting value for comparison
	TCCR1B|=(1<<CS10)|(1<<WGM12)|(1<<CS12);      //setting CS10 ,CS12 AND WGM12 ANSSIGN TO TCCR1B
	
}

ISR(TIMER1_COMPA_vect){                         
	PORTC=~(PORTC);                              //blinking LED
	
}