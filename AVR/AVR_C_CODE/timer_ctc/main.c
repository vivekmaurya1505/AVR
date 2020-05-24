/*
 * timer_ctc.c
 *
 * Created: 02-09-2019 18:55:20
 * Author : DESD
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
void timer1_init();
void timer1_delay(unsigned int );
#include <lcd.h>

int main(void)
{
	
	DDRC=0xff;
	   timer1_init();                               //timer1 initialization
	//set direction port c as a output for led
	while (1){                                         //infinite loop
		timer1_delay(10000);
		PORTC=~(PORTC);                // delay for 10 sec
	}
}
void timer1_init(){
	TCNT1=0;
	OCR1A=15999;
	TCCR1B|=(1<<CS10)|(1<<WGM12);
	
	
}
void timer1_delay(unsigned int time_ms){
	
	for (int i=0;i<time_ms;i++){
		TCNT1=0;
		while(!(TIFR&(1<<4)));            //check overflow condition
		//TCNT1=49536 increase upto 65535 for 1 ms
		TIFR|=(1<<OCF1A);                          //reset tov1 to 0
	}
}