/*
 * exam.c
 *
 * Created: 24-09-2019 07:35:53
 * Author : PRN_190840130111
 */


/*===========================================================TICKET BOOKING SYSTEM =====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

//=====================================================
/*lcd declaration */
#define LCD_PORT PORTA
#define RS PA0
#define EN PA2
//==================
void lcd_init();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void latch();
void lcd_string(char *str);
//=====================================================
/* Uart declaration*/
#define BAUDRATE 9600
void UART_Init( unsigned int ubrr );
void UART_Transmit( unsigned char data );
char UART_Receive( void );
void UART_STRING(char *str);
//======================================================
#define train_number_size 5
void ticket();
char ticket_match[train_number_size];
unsigned char ticket_no( void );

//===============
/* external interrupt declaration for switch for ticket confirmation*/
void ext_int();
//========================================================
int main(void)
{
  /*lcd initialization call*/
  lcd_init();
  /*uart initialization call*/
  UART_Init(103);
  /*call fuction for ticket booking*/
  ticket();

 

    while (1) 
    {		
    }
}

//==========================================================
void lcd_init(){
	/*direction set for lcd*/
	DDRA=0XF5;
	/*delay for lcd startup*/
	_delay_ms(20);
	/*lcd command */
	/* 4 bit lcd 5x7 matrix*/
	lcd_cmd(0x28);
	lcd_cmd(0x02);
	/*for clear lcd*/
	lcd_cmd(0x01);
	/*cursor increment*/
	lcd_cmd(0x06);
	/*cursor start first line*/
	lcd_cmd(0x80);
	
}
void lcd_cmd(unsigned char cmd){
	/*lcd command send to lcd port */
	LCD_PORT=cmd & 0xf0;
	/*call function for latch data to lcd */
	latch();
	/*lcd command send to lcd port shifting by 4*/
	LCD_PORT=(cmd<<4);
	/*call function for latch data to lcd */
	latch();
}
void lcd_data(unsigned char data){
	
	LCD_PORT=(data & 0xf0)|(1<<RS);
	/*call function for latch data to lcd */
	latch();
	LCD_PORT=(data<<4)|(1<<RS);
	/*call function for latch data to lcd */
	latch();
}

void latch(){

/*enable the PA2 FOR latch the data */
	PORTA|=(1<<EN);
	_delay_ms(15);
	/*disable the PA2 */
	PORTA&=~(1<<EN);
	_delay_ms(15);
}

void lcd_string(char *str){
	
	while (*str!=0){
		lcd_data((*str));
		str++;
	}
	
}


//======================================================================================================

void UART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR1H = 0x00;
	UBRR1L = ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	
}

void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

 char UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR1;
}
void UART_STRING(char *str){
	
	while (*str!=0){
		UART_Transmit((*str));
		str++;
	}
	
}
//================================================================================================================
unsigned char ticket_no( void )
{
	int i;
	for(i=0;i<train_number_size;i++){
	
		ticket_match[i]=UART_Receive();
		
	}
	ticket_match[i]='\0';
	return(strcmp(ticket_match,"12127"));
	
}

void ticket(){
	/*SEND DATA ON TERMINAL USING UART TRANSMITION FUNCTION*/
	 UART_STRING("\"==============WELCOME TO INDIAN RAILWAY==============\"\r\n\r\n");
	 UART_STRING("Intercity Express Train no:12127\r\n");
	 UART_STRING("Enter Train Number:   ");
	
	if (!(ticket_no())){
		
		while(UART_Receive()!='\r');
		  
		    UART_STRING("\r\n TRAIN  MUMBAI PUNE INTERCITY EXPRESS:\r\n");
			UART_STRING("\r\nPRESS SWITCH FOR CONFIRMATION \r\nSWITCH 1:AC\r\nSWITCH 2:SL\r\n");
			
	}
	else{
		
		UART_STRING("\r\nEnter Train No is Wrong Please Try Again:\r\n");
		 ticket();
	}
	
	 lcd_string("AVAILABE AC 30\r\n");
	 UART_STRING("AVAILABE AC 30\r\n\r\n");
	 /*cursor move on second line of lcd*/
	 lcd_cmd(0XC0);
	 lcd_string("AVALABLE SL 121");
	 UART_STRING("AVALABLE SL 121\r\n\r\n");
	
	 ext_int();
	 
}
//===============================================================================================================
void ext_int(){
	/* SET PORTE AS A PULLUP SO THAT IF WE PRESS A SWITCH THEN IT WILL SENSE A EXTERNAL INTERRUPT AND IT WILL BOOK A TICKET*/
	DDRE=0X00;
	PORTE=0XFF;
	/*ENABLE SWITCH 6 AND SWITCH 7*/
	EIMSK|=(1<<INT6)|(1<<INT7);
	/* ENABLE GLOBAL INTERRUPT */
	sei();
	
}

ISR(INT6_vect){
	
	/* DISABSBLE GLOBAL INTERRUPT SO THAT NO OTHER INTERRUPT COME */
	cli();
	/*for clear lcd*/
	lcd_cmd(0x01);
	lcd_string("confirmed in AC ");
	UART_STRING("confirmed in AC \r\n\r\n");
	UART_STRING(".................HAPPY JOURNEY................\r\n\r\n"); 
	UART_STRING(".................VISIT AGAIN................\r\n\r\n");
	/* REENABLE GLOBAL INTERRUPT */
	sei();
}
ISR(INT7_vect){
	
	/* DISABSBLE GLOBAL INTERRUPT SO THAT NO OTHER INTERRUPT COME */
	cli();
	/*for clear lcd*/
	lcd_cmd(0x01);
	lcd_string("confirmed in SL ");
	UART_STRING("confirmed in SL \r\n\r\n");
	UART_STRING(".................HAPPY JOURNEY................\r\n\r\n");
    UART_STRING(".................VISIT AGAIN................\r\n\r\n");
	/* REENABLE GLOBAL INTERRUPT */
	sei();
	
}

//======================================================

