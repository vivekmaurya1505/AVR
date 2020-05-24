/*
 * UART.c
 *
 * Created: 04-09-2019 15:04:51
 * Author :  PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#define _baud 9600
#include <util/delay.h>
#define my_ubrr F_CPU/16/_baud-1
void uart_init(unsigned int );
void uart_tx(unsigned char);
void data_string(char *);
int main(void)
{
	uart_init(103);
		data_string("abcdf");
   	 while (1) 
   	 {
	
   	 }
}

void uart_init(unsigned int ubrr){

	UCSR1B|=(1<<RXCIE1);
	UBRR1H=0;                          //HIGHER BIT 00
	UBRR1L=ubrr;                       //to set baud rate
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1)|(1<<TXCIE1);     // Enabling tx and rx pin
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);  
	sei();
}

 ISR(USART1_TX_vect){ 

 }
ISR(USART1_RX_vect){
 	
 	uart_tx(UDR1);  
	
 }
 
 void uart_tx(unsigned char data){
	
	 UDR1=data;
	 
	 
 }
 void data_string(char *str){
	 for(int i=0;str[i]!='\0';i++){
		 UDR1=str[i];
		 _delay_ms(10);
		 
	 }
	 
 }