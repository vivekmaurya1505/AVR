/*
 * UART INTERRUPT CHAR.c
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
//=========================================
int main(void)
{
	  // uart initialization
	uart_init(103);  
	//transmit data to UDR1                               
	UDR1='M';                                         
   	 while (1) 
   	 {
	
   	 }
}

void uart_init(unsigned int ubrr){

  //receiver interrupt enable
	UCSR1B|=(1<<RXCIE1);       
	//HIGHER BIT 00                       
	UBRR1H=0;    
	 //to set baud rate                                      
	UBRR1L=ubrr;    
	// Enabling tx and rx pin and transmitter interrupt enable                                
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1)|(1<<TXCIE1);    
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);  
	// global interrupt enable
	sei(); 
}
	                                          
// ISR for transmitter 
 ISR(USART1_TX_vect){ 

 }
 // ISR for receiver
ISR(USART1_RX_vect){
 	
 	uart_tx(UDR1);  
	
 }
void uart_tx(unsigned char data){
	
	UDR1=data;
	
	
}