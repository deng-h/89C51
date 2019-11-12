#include "STC15Fxxxx.h"
#include "STDEF.h"


#define ADC_Power 0x80     //ADC电源控制位
#define ADC_Flag 0x10      //ADC完成标志
#define ADC_Start 0x08     //ADC启动


#define ADC_Speed_LL 0x00   //540个时钟
#define ADC_Speed_L 0x20    //360个时钟
#define ADC_Speed_H 0x40    //180个时钟
#define ADC_Speed_HH 0x60   // 90个时钟

uchar Channel_Sel;
uchar AD_Result[8];

void ADC_INIT(void)
{
	P1ASF = 0xFF;             //设置P1口为ADC输入
	ADC_RES = 0;                    //清除结果寄存器
	Channel_Sel=0;
	ADC_CONTR = ADC_Power | ADC_Speed_LL | ADC_Start | Channel_Sel;
}

/*----------------------------
ADC中断
----------------------------*/
void ADC_ISR() interrupt 5 using 1
{
	ADC_CONTR &= ~ADC_Flag;     
	AD_Result[Channel_Sel]=ADC_RES;
	Channel_Sel=(Channel_Sel+1)&0x07;
	ADC_CONTR = ADC_Power | ADC_Speed_LL | ADC_Start | Channel_Sel;
}

uchar ADC_Read(uchar channel)
{
	return AD_Result[channel];
}
