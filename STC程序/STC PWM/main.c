#include "STC15F2K60S2.h"
#include "PWM.h"
#include "UART.h"
#include "ADC.h"
typedef unsigned int uint;
typedef unsigned char uchar;

uint count=0;
uchar num[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2e};
						//����0~9ASCII���ʮ�����Ʊ�ʾ�����С�����ʮ�����Ʊ�ʾ
float Dec_data[8];  //ת����10����

void Dec2Char(float dec)   //������ʾ
{
	int a,b,c;     //ȡʮ���Ƶ�ǰ��λ
	if(dec<0)
	{
		UART_Write_byte(0x2d);
		dec=-dec;
	}
	a=dec*100/100;
	dec=dec-a;
	b=dec*100/10;
	dec=dec-0.1*b;
	c=dec*1000/10;
	UART_Write_byte(num[a]);
	UART_Write_byte(num[10]);
	UART_Write_byte(num[b]);
	UART_Write_byte(num[c]);
	UART_Write_byte(0x56);   //V
	UART_Write_byte(0x09);   //TAB

}
void Display()
{
	if(count>=3000)
	{
		count=0;
		Dec_data[0]=5*(ADC_Read(0)/256.0);  //��ȡ��ת����P10��
		Dec_data[1]=5*(ADC_Read(1)/256.0);  //��ȡ��ת����P11��
		Dec2Char(Dec_data[0]);							 //��ʾ
		Dec2Char(Dec_data[1]);							 //��ʾ
		Dec2Char(Dec_data[1]-Dec_data[0]);							 //��ʾ
		UART_Write_byte('\n');
	}
}
void Timer0_Init(void)		
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		
	TL0 = 0xCD;		
	TH0 = 0xD4;		
	TF0 = 0;		
	ET0 = 1;    
	TR0 = 1;		
}

void main()
{
	EA=0;
	PWM_Init();
	UART_Init();
	Timer0_Init();
	ADC_Init();
	EA=1;
	EADC=1; //��A/Cת���ж�
	PWM_Out(0,50);
	PWM_Out(0,70);
	while(1);
}

void Timer0_Routine(void) interrupt 1
{
	count++;
}