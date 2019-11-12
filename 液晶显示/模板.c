#include <reg51.h>
#include "lcd.h"

sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;

void delay(unsigned int i)
{
	while(i--);
}
void main()
{
	LcdInit();
	LcdWriteCom(0x01+0x80);
	LcdWriteData('*');
	while(1)
	{
	}
}