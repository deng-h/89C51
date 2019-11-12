#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                           0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//0到f数显的十六进制
void delay(u16 i)    //延时
{
	 while(i--);
}

void main()
{
	if(key1==0)         //按键1
	{
		LSA=0;LSB=0;LSC=0;
		delay(1000);   
		if(key1==0)
		{
			P0=list[0];
		}
		while(!key1);
	}
	if(key2==0)         //按键2
	{
		LSA=1;LSB=0;LSC=0;
		delay(1000);   
		if(key2==0)
		{
			P0=list[1];
		}
		while(!key2);;
	}
	if(key3==0)         //按键3
	{
		LSA=0;LSB=1;LSC=0;
		delay(1000);   
		if(key3==0)
		{
			P0=list[2];
		}
		while(!key3);
	}
	if(key4==0)         //按键4
	{
		LSA=1;LSB=1;LSC=0;
		delay(1000);   
		if(key4==0)
		{
			P0=list[3];
		}
		while(!key4);
	}
	
}