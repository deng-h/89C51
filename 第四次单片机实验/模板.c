#include <reg52.h>
typedef unsigned int uint;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

char code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
									0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(uint i);   
int keypress();

void main()
{
	LSA=0;LSB=0;LSC=0;  //选中第1个数码
	while(1)
	{
		keypress();
		P0=list[keypress()];
	}
}

void delay(uint i)   
{
	 while(i--);
}

int keypress()   //返回显示的数字
{
	int digit=0;
	P1=0x0f;         
	if(P1!=0x0f)
	{
		delay(1000);
		if(P1!=0x0f)
		{
			switch(P1)
			{
				case(0x07):digit=1;break;
				case(0x0b):digit=2;break;
				case(0x0d):digit=3;break;
				case(0x0e):digit=4;break;
			}
		}
	}
	P1=0xf0;         
	if(P1!=0xf0)
	{
			switch(P1)
			{
				case(0x70):digit=digit;break;
				case(0xb0):digit=digit+4;break;
				case(0xd0):digit=digit+8;break;
				case(0xe0):digit=digit+12;break;
			}
	}
	 delay(1000);
	 return digit;
}