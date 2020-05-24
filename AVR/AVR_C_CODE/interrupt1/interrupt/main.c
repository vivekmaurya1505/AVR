/*
 * interrupt.c
 *
 * Created: 14-09-2019 14:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void ext_int_init();
int main()
{
	ext_int_init();
	  while(1)
	  {	  
	  }
}
  
  void ext_int_init(){
	  
  	DDRC=0xff;
  	DDRE= 0x00; //Configure Port E as input port
  	PORTE=0xff;  //Enable pull up resistor
  	EICRB=0x00;  
  	EIMSK=0xc0;
  	sei();
	  
  }
  
  ISR(INT1_vect){
	  cli();
  	PORTC=~PORTC;
	  sei();
  }