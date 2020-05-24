/*
 * BUZZER.c
 *
 * Created: 17-09-2019 13:42:02
 * Author :PRN 19084013020111,PRN 19084013020112 
 */ 

#include <avr/io.h>
#define buzzer PA3

int main(void)
{
	
   DDRA|=(1<<buzzer);
    while (1) 
    {
		PORTA|=(1<<buzzer);
		for (unsigned int i=0;i<300000;i++);
		PORTA&=~(1<<buzzer);
		for (unsigned int i=0;i<300000;i++);
    }
}

