/*
通过差值控制
*/
#include "STC15F2K60S2.h"
#include "PWM.h"
#include "UART.h"
#include "ADC.h"
#define left 0
#define right 1

typedef unsigned int uint;
typedef unsigned char uchar;

//*********用于向电脑传送电感的ADC值*************//
uint count=0;
uchar num[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2e};
						//数字0~9ASCII码的十六进制表示，外加小数点的十六进制表示
float Dec_data[8];  //转换成10进制
void Dec2Char(float dec)   //电脑显示
{
	int a,b,c;     //取十进制的前三位
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
		Dec_data[0]=5*(ADC_Read(0)/256.0);  //读取并转换，P10口
		Dec_data[1]=5*(ADC_Read(1)/256.0);  //读取并转换，P11口
		Dec2Char(Dec_data[0]);							 //显示
		Dec2Char(Dec_data[1]);							 //显示
		Dec2Char(Dec_data[0]-Dec_data[1]);							 //显示
		UART_Write_byte('\n');
	}
}
void DisplayHex()
{
	if(count>=3000)
	{
		UART_Write_byte(ADC_Read(0));
		UART_Write_byte(ADC_Read(1));
		UART_Write_byte(ADC_Read(0)-ADC_Read(1));
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

void Timer0_Routine(void) interrupt 1
{
	count++;
}
//**********************************************//
void main()
{
	uchar motor[2];
	float delta,differ;
	EA=0;
	PWM_Init();
	UART_Init();
	Timer0_Init();
	ADC_Init();
	EA=1;
	EADC=1; //打开A/C转换中断
	while(1)
	{
		motor[0]=ADC_Read(0);  
	  motor[1]=ADC_Read(1);  
	  delta=motor[0]-motor[1]-0x05;//补偿因情况而定
	  differ=delta;  //比例因情况而定
	  PWM_Out(left,72-differ);  //基础PWM因情况而定
	  PWM_Out(right,65+differ);  
//	  differ=delta*0.8;
//	  PWM_Out(left,80);  
//	  PWM_Out(right,85);  
//  Display(); 
	  //DisplayHex();
	}
}

