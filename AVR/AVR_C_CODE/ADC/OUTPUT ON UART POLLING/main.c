
#define F_CPU 16000000                // CLK freq
#include <avr/io.h>                   //avr library files 
#include <stdio.h>                    //to use snprintf function
#include <util/delay.h>               // for delay
#include <lcd.h>                      // lcd header file
#define _baud 9600                    // baud rate
void uart_init(unsigned int );        // declaration of uart initialization function                    
void uart_tx(unsigned char);          // declaration of uart transmission function
void uart_string(char *);             //declaration of fuction which converts int data into string
void adc_init();                      //declaration of adc initialization function                   
unsigned int adc_start();             //declaration of adc start function
int main(void)                         
{
	
	char buf1[10];                   
	unsigned int DOUT=0;
	DDRC=0xff;
	unsigned int data;
	lcd_init();
	adc_init();
	//calculated value of ubrr is 103(ubrr=fosc/16/baud_rate-1)
	uart_init(103);
	while (1)
	{
		// ADC conversion result is catching into data variable
		data=adc_start();
		//calculation of digital output
		DOUT=(data*(5000/1024));
		
//snprintf() function formats and stores a series of characters and values in the array buffer.
		snprintf(buf1, 10, "%dmv",DOUT);
		lcd_string(buf1);
		_delay_ms(1000);
		PORTC=0xf0;
		uart_string(buf1);

	}
}
void adc_init()

{   //ADC0 IS SELECTED BY SETTING MUX5:0 TO ZERO.
	// Vref set to 5 volt and 8 bits in higher ADCH and 2 bits in lower ADCL
	ADMUX |= (1<<REFS0);
	//prescaler set to 128 that is 125 KHz adc clk freq
	ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	//ADCSRB -> ADTS2:0  free running mode -- set to zero
}
unsigned int adc_start()
{
	//to set start conversion bit of reg ADCSRA
	ADCSRA |=(1<<ADSC); 
	//To check if conversion is completed or not   
	while(!(ADCSRA &(1<<ADIF)));
	//PORTC = ADC;
	return ADC;
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
