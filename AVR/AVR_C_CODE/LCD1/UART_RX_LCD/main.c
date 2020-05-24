/*
 *UART_RX_LCD.c
 *
 * Created: 11-09-2019 10:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#define _baud 9600
#include <util/delay.h>
#define my_ubrr F_CPU/16/_baud-1
//=============================
void uart_init(unsigned int );
void uart_rx();
void uart_tx(unsigned char);
void uart_string(char *);
//============================================================================================================
#define  LCD_PORT PORTA
#define  RS PA0                          // PORTA pin PA0 is used for command and data, RS is connected to pin PA0
#define  EN PA2                         // PORTA pin PA2 is used for enable in lcd to fetch data
//============================
void lcd_cmd(unsigned int );            //command function
void lcd_data(unsigned char );          //data function
void lcd_init();                        //lcd initialization function
void en();                              //enable function for lcd
void lcd_string(char *);                //string function for lcd
void lcd_result(int ,char *, int );     //print result value,(result,buffer[size],base)

//=============================================================================================================
int main(void)
{	
	lcd_init();
	uart_init(103);
	
	while (1)
	{		   
		 uart_rx();
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
	lcd_data(UDR1);                  //to display received data on lcd
	
}

//===============================================================================================
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