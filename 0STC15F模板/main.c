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
	
}