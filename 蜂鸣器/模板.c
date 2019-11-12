#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit beep=P1^5;

void delay(u16 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
		beep=~beep;
		delay(100);
	}
}