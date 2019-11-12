#include "STC15Fxxxx.h"
#include "STDEF.h"
#include "PWM.h"
#include "ADC.h"
#include "UART.h"

#define T50MS (65536-MAIN_Fosc*50/1000/12)		//50ms��ʱ

uchar base = 40;

uchar sec;

void Timer1_Init(void)
{

	TMOD &= 0x0F;		//��ʱ������ģʽ1��16λ��ʱģʽ
	TH1  = T50MS>>8;
	TL1  = T50MS;		//��ʱ50ms
	ET1  = 1;			//�򿪶�ʱ��1�ж�
	TR1  = 1;			//��ʱ��1������
	sec = 0;
}

void UART_Voltage(float buf)   //���ڴ��ص�ѹֵ
{
	uchar a,b,c;     //��ѹֵ a.bc
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

	

		if (sec == 40)		//1�뵽
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
		TL0  = T50MS;		//��ʱ50ms
		sec++;			//50ms��,sec++
}
