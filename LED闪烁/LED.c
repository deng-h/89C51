#include <reg52.h>
typedef unsigned int u16;
void delay(u16 i);
sbit led1=P2^3;
sbit led2=P2^2;
sbit key1=P3^1;

u16 a=100;

void keypress()
{
	if(key1==0)    
	{
		delay(100);  
		if(key1==0)  
		{
			 a+=100;
		}
		while(!key1);   
	}
}

void main()
{
	while(1)
	{
		keypress();
		led1=0;
		led2=0;
		delay(a);
		led1=1;
		led2=1;
		delay(a);
	}
	
}
void delay(u16 i)
{
	while(i--);
}

