/*
 * UART.c
 *
 * Created: 04-09-2019 15:04:51
 * Author : DESD
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#define _baud 9600
#include <lcd.h>
#include <util/delay.h>
#define my_ubrr F_CPU/16/_baud-1
void uart_init(unsigned int );
void uart_rx();
void uart_tx(unsigned char);
int main(void)
{
	lcd_init();
	
	uart_init(my_ubrr);
  
    while (1) 
    {
		uart_tx('m');
		_delay_ms(1000);
		
    }
}

void uart_init(unsigned int ubrr){

	UCSR1B|=(1<<RXCIE1);
	UBRR1H=0;                          //HIGHER BIT 00
	UBRR1L=ubrr;                       //to set baud rate
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1);     // Enabling tx and rx pin
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);  
		// for transmitting 8 bit data
	sei();
}

void uart_tx(unsigned char data){
while(!((UCSR1A)&(1<<UDRE1)));     //to check if UDR is empty or not if empty then load data to UDR
UDR1=data;                           
}

// ISR(USART1_TX_vect){
// 	UDR1='a'; 
// 	
// }

// void uart_rx(){
// 	while (!((UCSR1A)&(1<<RXC1)))    //to check if reception of data is completed by controller or not.if completed then
// 	{                                //come out of the loop
// 	}
// 	lcd_data(UDR1);                  //to display received data on lcd
// 	
// }
ISR(USART1_RX_vect){
	
	lcd_data(UDR1);  
	
}
