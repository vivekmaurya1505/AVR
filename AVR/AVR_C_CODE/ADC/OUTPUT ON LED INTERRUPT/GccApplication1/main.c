/*
 * OUTPUT ON LED INTERRUPT.c
 *
 * Created: 17-09-2019 13:38:00
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000                // CLK freq
#include <avr/io.h>                   //avr library files
#include <util/delay.h>               // for delay
#include <avr/interrupt.h>            //header file for interrupt
void adc_init();                      //declaration of adc initialization function
unsigned int adc_start();             //declaration of adc start function
int main(void)
{
	DDRC=0xff;
	adc_init();
	while (1)
	{
		
	}
}
void adc_init()

{   //ADC0 IS SELECTED BY SETTING MUX5:0 TO ZERO.
	// Vref set to 5 volt and 8 bits in higher ADCH and 2 bits in lower ADCL
	ADMUX |= (1<<REFS0);
	sei();
	//prescaler set to 128 that is 125 KHz adc clk freq
	ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	//ADCSRB -> ADTS2:0  free running mode -- set to zero
	// To set start conversion bit
	ADCSRA |=(1<<ADSC);
	//To enable interrupt
	ADCSRA|=(1<<ADIE);
	
	
}
//ADC interrupt routine
ISR(ADC_vect)
{
	PORTC=ADC;
	ADCSRA |=(1<<ADSC);
}
