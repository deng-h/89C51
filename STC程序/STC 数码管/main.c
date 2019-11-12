#include <STC15F2K60S2.h>
typedef unsigned int uint;
typedef unsigned char uchar;
void delay_ms(uint t)
{
	while(t--)
	{
		uchar i=11,j=190;
		do
		{
			while(--j);
		}while(--i);
	}
}

void main()
{
	P00=1;
	P02=0;
	P03=1;
	P04=0;
}