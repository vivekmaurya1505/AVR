/*
 * OUTPUNT ON UART INTERRUPT.c
 *
 * Created: 17-09-2019 14:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000                // CLK freq
#include <avr/io.h>                   //avr library files
#include <stdio.h>                    //to use snprintf function
#include <util/delay.h>               // for delay
#include <lcd.h>                      // lcd header file
#include <avr/interrupt.h>            //header file for interrupt
#define _baud 9600                    // baud rate
void uart_init(unsigned int );        // declaration of uart initialization function
void uart_tx(unsigned char);          // declaration of uart transmission function
void uart_string(char *);             //declaration of fuction which converts int data into string
void adc_init();                      //declaration of adc initialization function
unsigned int adc_start();             //declaration of adc start function
int main(void)
{
	DDRC=0xff;                        
	lcd_init();
	//calculated value of ubrr is 103(ubrr=fosc/16/baud_rate-1)
	uart_init(103);
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

void uart_init(unsigned int ubrr){
	//HIGHER BIT 00
	UBRR1H=0;
	//to set baud rate
	UBRR1L=ubrr;
	// Enabling tx and rx pin
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1);
	// for transmitting 8 bit data
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);
	
}

void uart_tx(unsigned char data){
	//to check if UDR is empty or not if empty then load data to UDR
	while(!((UCSR1A)&(1<<UDRE1)));
	UDR1=data;
	
}
// To send string to uart character by character
void uart_string(char * str){
	for(unsigned int i=0;str[i]!='\0';i++){
		uart_tx(str[i]);
	}
}

ISR(ADC_vect)
{   
	char buf1[20];
	unsigned int DOUT=0;
	DOUT=(ADC*(5000/1024));

	//snprintf() function formats and stores a series of characters and values in the array buffer.
	snprintf(buf1, 20, "LDR_ADC_V=%dmv",DOUT);
	
	_delay_ms(2000);
	lcd_cmd(0x01);
	lcd_string(buf1);
	
	uart_string(buf1);
	//To clear interrupt flag
	ADCSRA|=(1<<ADIF);
	//To reset start conversion bit
	ADCSRA |=(1<<ADSC);
}
