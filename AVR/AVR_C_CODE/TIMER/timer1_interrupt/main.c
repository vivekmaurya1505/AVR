/*
 * timer1_interrupt.c
 *
 * Created: 04-09-2019 07:46:56
 * Author :  PRN 19084013020111,PRN 19084013020112 
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
void timer1_init();
//================================
int main(void)
{
	DDRC=0XFF;                   //set direction port c as an output for led
	
	timer1_init();              //timer1 initialization
	while (1)
	{
		
	}
}
void timer1_init(){
	sei();                        //global interrupt enable
	TIMSK|=(1<<TOIE1);            //timer 1 interrupt enable
	TCNT1=49536;                  // set value
	TCCR1B|=(1<<CS10)|(1<<CS12);    //prescaler of  1024
}
ISR(TIMER1_OVF_vect){              // ISR for timer1
	
	
	PORTC =~PORTC;                     //led toggle
	TCNT1=49536;                      //TCNT1=49536 increase upto 65535 for 1 ms 
	
}
