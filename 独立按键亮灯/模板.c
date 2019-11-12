#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit key1=P3^1;
void delay(u16 i)
{
	while(i--);
}
void keypress()
{
	if(key1==0)    //判断P3^1是否与地连接，即按键是否按下
	{
		delay(1000);  //延时1ms，按下防抖
		if(key1==0)   //再次判断是否与地连接
		{
			led1=~led1;  //P2^0口1、0反转，
		}
		while(!key1);   //如果为0，循环，直至为1（松开防抖）
	}
}
void main()
{
	keypress();
}




