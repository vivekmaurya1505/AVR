/*
 * timer_ctc.c
 *
 * Created: 02-09-2019 18:55:20
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
void timer1_init();
void timer1_delay(unsigned int );


int main(void)
{
	
	DDRC=0xff;                                       //set direction port c as a output for led
	   timer1_init();                               //timer1 initialization
	                                                
	while (1){                                        //infinite loop
		timer1_delay(10000);
		PORTC=~(PORTC);                               // delay for 10 sec
	}
}
void timer1_init(){
	TCNT1=0;                                       // counter value initializes to zero which reaches upto maximum value stored in OCR1A reg
	OCR1A=15999;                                   // maximum value is loaded into OCR1A reg 
	TCCR1B|=(1<<CS10)|(1<<WGM12);                 //setting CS10 AND WGM12 ANSSIGN TO TCCR1B for no prescaling and ctc mode selection
	
	
}
void timer1_delay(unsigned int time_ms){
	
	for (int i=0;i<time_ms;i++){ 
		TCNT1=0;
		while(!(TIFR&(1<<4)));            //check overflow condition
		                                  //TCNT1=49536 increase upto 65535 for 1 ms
		TIFR|=(1<<OCF1A);                 //reset tov1 to 0
	}
}