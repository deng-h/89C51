//´Ó»ú´úÂë

#include <reg52.h>
#include "UART.h"
#include "digital.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void main()
{
	LSA=0;LSB=0;LSC=0;
	P0=list[0];
	Uart_init();
	while(1);
}
