#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                           0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
u16 digit;
													 
void delay(u16 i)   
{
	 while(i--);
}
void keypress()
{
	 P1=0x0f;          //高四位为0，低四位为1，如果低位出现0，可判断哪一列
	 if(P1!=0x0f)
	 {
		 delay(1000);
		 if(P1!=0x0f)
		 {
			 switch(P1)
			 {
				 case(0x07):digit=0;break;
				 case(0x0b):digit=1;break;
				 case(0x0d):digit=2;break;
				 case(0x0e):digit=3;break;
			 }
		 }
	 }
		P1=0xf0;         //高四位为1，低四位为0，如果高位出现0，可判断行。从而判断哪一按键按下
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
}
void main()
{
	while(1)
	{
		keypress();
		switch(digit)
		{
			case(0):LSA=0;LSB=0;LSC=0;break;
			case(1):LSA=1;LSB=0;LSC=0;break;
			case(2):LSA=0;LSB=1;LSC=0;break;
			case(3):LSA=1;LSB=1;LSC=0;break;
			case(4):LSA=0;LSB=0;LSC=1;break;
			case(5):LSA=1;LSB=0;LSC=1;break;
			case(6):LSA=0;LSB=1;LSC=1;break;
			case(7):LSA=1;LSB=1;LSC=1;break;
			case(8):LSA=0;LSB=0;LSC=0;break;
			case(9):LSA=1;LSB=0;LSC=0;break;
		  case(10):LSA=0;LSB=1;LSC=0;break;
			case(11):LSA=1;LSB=1;LSC=0;break;
			case(12):LSA=0;LSB=0;LSC=1;break;
			case(13):LSA=1;LSB=0;LSC=1;break;
			case(14):LSA=0;LSB=1;LSC=1;break;
			case(15):LSA=1;LSB=1;LSC=1;break;
		}
			P0=list[digit];
		delay(1000);
		P0=0x00;
	}
}















