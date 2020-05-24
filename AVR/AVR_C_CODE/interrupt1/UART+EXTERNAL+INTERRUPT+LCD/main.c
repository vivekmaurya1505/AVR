/*
 * uart_practice.c
 *
 * Created: 15-09-2019 08:44:42
 * Author :  PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define ubr 103
#define size 10
void uart_init();
void uart_tx( char data);
void uart_rx();
void uart_str();
void ext_init();
char str[size];
//===========================
#include<stdlib.h>

#define  LCD_PORT PORTA
#define  RS PA0                          // PORTA pin PA0 is used for command and data, RS is connected to pin PA0  
#define  EN PA2                     // PORTA pin PA2 is used for enable in lcd to fetch data
void lcd_cmd(unsigned int );            //command function 
void lcd_data(unsigned char );          //data function
void lcd_init();                        //lcd initialization function
void en();                              //enable function for lcd
void lcd_string(char *);                //string function for lcd

//==============================================
int main(){
	
	
	DDRC=0xff;
	lcd_init();
	uart_init();
	ext_init();
	uart_str(str);
	while (1)
	{
		
		
	}
	
}
void uart_init(){
	
	UBRR1H=0x00;
	UBRR1L=ubr;
	UCSR1B|=(1<<RXEN1)|(1<<TXEN1);
	
}
void uart_tx(char data){
	
	while(!((UCSR1A)&(1<<UDRE1)));
	
	UDR1=data;
	
}
void uart_str(char str[]){
	
	for(int i=0;i<size;i++){
	while (!((UCSR1A) &(1<<RXC1)));
		
		str[i]=UDR1;
		PORTC=~PORTC;
	}
}

void ext_init(){ 
	
	DDRE=0X00;
	PORTE=0XFF;
	EIMSK=0XC0;
	sei();
}
ISR(INT7_vect){
	cli();
	PORTC=0xf0;
	lcd_string(str);
	sei();
}

//====================================================================================================
void lcd_cmd(unsigned int COMMAND){
	
	LCD_PORT=(COMMAND & 0xf0);                   //msb data copy to lcd_port
	en();                                        // lcd_port data copy to lcd
	LCD_PORT=((COMMAND & 0x0f)<<4);              //lsb data shifted by 4
	en();                                        // lcd_port data copy to lcd
}
void lcd_data(unsigned char DATA){
	
	LCD_PORT=(DATA & 0xf0)|(1<<RS);               //msb data copy to lcd_port
	en();                                         // lcd_port data copy to lcd
	LCD_PORT=((DATA )<<4)|(1<<RS);                //lsb data shifted by 4
	en();                                         // lcd_port data copy to lcd
}
void en(){
	
	LCD_PORT|=(1<<EN);
	_delay_ms(15);
	LCD_PORT&=~(1<<EN);
	_delay_ms(5);
}
void lcd_init(){
	_delay_ms(20);         //power on delay for lcd
	DDRA=0xf5;             // set port as a lcd outport 11110101
	lcd_cmd(0x02);         //Return home
	lcd_cmd(0X28);         //2 lines and 5×7 matrix (4-bit mode)
	lcd_cmd(0X01);         //Clear display screen
	lcd_cmd(0X0f);
	lcd_cmd(0X06);         //Increment cursor (shift cursor to right)
	lcd_cmd(0X80);         //Force cursor to beginning to 1st line
}
void lcd_string(char * str){
	for(unsigned int i=0;str[i]!='\0';i++){
		lcd_data(str[i]);
	}
}
//========================================================================================

