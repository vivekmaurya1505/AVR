/*
 * UART_STRING.c
 *
 * Created: 13-09-2019 10:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#define _baud 9600
#include <util/delay.h>
#define my_ubrr F_CPU/16/_baud-1
void uart_init(unsigned int );
void uart_rx();
void uart_tx(unsigned char);
void uart_string(char *); 
int main(void)
{	char buf[50]="AAAAstringwe";

	uart_init(103);
	
	while (1)
  {		    uart_rx();
		uart_string(buf);
		//_delay_ms(1000);
		
	}
}

void uart_init(unsigned int ubrr){
	UBRR1H=0;                          //HIGHER BIT 00
	UBRR1L=ubrr;                       //to set baud rate
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1);     // Enabling tx and rx pin
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);  // for transmitting 8 bit data
	
}

void uart_tx(unsigned char data){
	while(!((UCSR1A)&(1<<UDRE1)));     //to check if UDR is empty or not if empty then load data to UDR
	UDR1=data;
	UCSR1A|=(1<<UDRE1);
	
}
void uart_rx(){
	while (!((UCSR1A)&(1<<RXC1)));    //to check if reception of data is completed by controller or not.if completed then
	                               //come out of the loop
	uart_tx(UDR1);                  //to display received data 
	
}

// To send string to uart character by character
void uart_string(char * str){
	for(unsigned int i=0;str[i]!='\0';i++){
		uart_tx(str[i]);
		
	}
}