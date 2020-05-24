/*
 * OUTPUT ON LED POLLING.c
 *
 * Created: 17-09-2019 10:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
void adc_init();
void adc_start();
int main(void)
{  
	DDRC=0xff;
	adc_init();
    while (1) 
    { 
		adc_start();
		_delay_ms(100);
    }
}
void adc_init()

{   //ADC0 IS SELECTED BY SETTING MUX5:0 TO ZERO.
	// Vref set to 5 volt and 8 bits in higher ADCH and 2 bits in lower ADCL
	ADMUX |= (1<<REFS0)|(1<<ADLAR);
	//prescaler set to 128 that is 125 KHz adc clk freq
	ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    //ADCSRB -> ADTS2:0  free running mode -- set to zero
}

void adc_start()
{
	ADCSRA |=(1<<ADSC);
	while(!(ADCSRA &(1<<ADIF)));
	PORTC = ADCH;
	ADCSRA|=(1<<ADIF);
}