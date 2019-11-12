//主机代码(主函数)

#include <reg52.h>
#include "UART.h"
#include "display.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit PWM=P1^0; //控制直流电机

extern count;
void main()
{
	LSA=0;LSB=0;LSC=0;
	P0=list[0];
	Uart_init();
	while(1)
	{
		if(count%2==0) PWM=0;
		else PWM=1;
	}
}

