/*
 * timer1.c
 *
 * Created: 02-09-2019 04:37:52
 * Author : DESD
 */ 
#define F_CPU 16000000UL                             
#include <avr/io.h>                                  
void timer1_init();
void timer1_delay(unsigned int );


int main(void)
{ 
	DDRC=0xff;        
	timer1_init();                                     //timer1 initialization
	                               //set direction port c as a output for led
    while (1){                                         //infinite loop
			timer1_delay(1000);      
			PORTC=~(PORTC);                // delay for 10 sec                      
	}   
}
void timer1_init(){
	TCCR1B|=(1<<CS10);   
	
}
 void timer1_delay(unsigned int time_ms){
	 
	 for (int i=0;i<time_ms;i++){
		 TCNT1=49536;
		while(!(TIFR&(1<<2)));            //check overflow condition 
		                             //TCNT1=49536 increase upto 65535 for 1 ms 
		TIFR|=(1<<TOV1);                          //reset tov1 to 0
	 }	
 }
