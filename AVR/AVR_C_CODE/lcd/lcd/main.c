/*
 * lcd.c
 *
 * Created: 01-09-2019 05:03:40
 * Author : DESD
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdlib.h>

#define  LCD_PORT PORTA
#define  RS PA0                          // PORTA pin PA0 is used for command and data, RS is connected to pin PA0  
#define  EN PA2                         // PORTA pin PA2 is used for enable in lcd to fetch data
void lcd_cmd(unsigned int );            //command function 
void lcd_data(unsigned char );          //data function
void lcd_init();                        //lcd initialization function
void en();                              //enable function for lcd
void lcd_string(char *);                //string function for lcd
void lcd_result(int ,char *, int );     //print result value,(result,buffer[size],base)

 
int main(void)
{
		lcd_init();
		lcd_cmd(0x80);
		lcd_string("hello");
		lcd_cmd(0xC0);
		
		int result1=12;
		char buffer1[5];
		lcd_result(result1,buffer1,10);
		
    while (1) 
    {
		
	 }
}

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
void lcd_result(int result,char *buffer,int base){
	lcd_string(itoa(result, buffer, base));
}