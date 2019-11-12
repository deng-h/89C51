#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
void delay(u16 i)
{
	while(i--);
}
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                           0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void main()
{
	int i;
	LSA=0;    //Î»Ñ¡£¬ÈÃLED1¶ËÎª0
	LSB=0;
	LSC=0;
	for(i=0;i<16;i++)
	{
		P0=list[i];
		delay(9999999);
	}
}