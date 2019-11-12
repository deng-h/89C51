#include "STC15Fxxxx.h"
#include "STDEF.h"
#include "PWM.h"
#include "ADC.h"
#include "UART.h"

#define T50MS (65536-MAIN_Fosc*50/1000/12)		//50ms定时

uchar base = 40;

uchar sec;

void Timer1_Init(void)
{

	TMOD &= 0x0F;		//定时器工作模式1，16位定时模式
	TH1  = T50MS>>8;
	TL1  = T50MS;		//定时50ms
	ET1  = 1;			//打开定时器1中断
	TR1  = 1;			//定时器1待启动
	sec = 0;
}

void UART_Voltage(float buf)   //串口传回电压值
{
	uchar a,b,c;     //电压值 a.bc
	a=buf*100/100;
	buf=buf-a;
	b=buf*100/10;
	buf=buf-0.1*b;
	c=buf*100;
	UART_Write_Byte('0'+ a);
	UART_Write_Byte('.');
	UART_Write_Byte('0'+ b);
	UART_Write_Byte('0'+ c);
	UART_Write_Byte('V');   //V
	UART_Write_Byte(0x09);  //TAB
}

void main()
{
	float Voltage_Left , Voltage_Right, differ;
	Timer1_INIT();
	UART_INIT();
	ADC_INIT();
	PWM_INIT();
	
	
	EADC=1;
	EA = 1;
	
	PWM_Out(left , 40);
	PWM_Out(right , 40);
	
	
	while(1)
	{
		Voltage_Left  = ADC_Read(0)/51.0;
		Voltage_Right = ADC_Read(1)/51.0;
		differ=Voltage_Left - Voltage_Right;



		if (differ < 0)
		{
			PWM_Out(left, 50);
			PWM_Out(right, 30);
		}

		if (differ > 0)
		{
	   		PWM_Out(right, 50);
			PWM_Out(left, 30);
		}

	

		if (sec == 40)		//1秒到
		{
			UART_Voltage(Voltage_Left);
			UART_Voltage(Voltage_Right);
			UART_Voltage(differ);
			UART_Write_Byte('\n');
			
			sec = 0;
		}
	
	}

}

void timer1() interrupt TIMER1_VECTOR using 1
{
		TH0  = T50MS>>8;
		TL0  = T50MS;		//定时50ms
		sec++;			//50ms到,sec++
}
