/*
 * OUTPUNT ON LCD POLLING.c
 *
 * Created: 17-09-2019 11:38:22
 * Author : PRN 19084013020111,PRN 19084013020112 
 */ 
#define F_CPU 16000000                // CLK freq
#include <avr/io.h>                   //avr library files
#include <stdio.h>                    //to use snprintf function
#include <util/delay.h>               // for delay
void adc_init();                      //declaration of adc initialization function
unsigned int adc_start();             //declaration of adc start function

//======================================
#define  LCD_PORT PORTA
#define  RS PA0                          // PORTA pin PA0 is used for command and data, RS is connected to pin PA0
#define  EN PA2                         // PORTA pin PA2 is used for enable in lcd to fetch data
void lcd_cmd(unsigned int );            //command function
void lcd_data(unsigned char );          //data function
void lcd_init();                        //lcd initialization function
void en();                              //enable function for lcd
void lcd_string(char *);                //string function for lcd
//=======================================
int main(void)
{
	
	char buf1[10];
	unsigned int DOUT=0;
	DDRC=0xff;
	unsigned int data;
	lcd_init();
	adc_init();
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

//==============================================


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
	
	//lcd enable for latching data
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