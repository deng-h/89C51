#include "STC15Fxxxx.h"
#include "stdint.h"


#define ADC_POWER 0x80     //ADC电源控制位
#define ADC_FLAG 0x10      //ADC完成标志
#define ADC_START 0x08     //ADC启动


#define ADC_SPEEDLL 0x00   //540个时钟
#define ADC_SPEEDL 0x20    //360个时钟
#define ADC_SPEEDH 0x40    //180个时钟
#define ADC_SPEEDHH 0x60   // 90个时钟

uint8_t ChannelSel;
uint8_t AD_Result[8];

void ADC_Init(void)
{
	P1ASF = 0xff;             //设置P1口为ADC输入
	ADC_RES = 0;                    //清除结果寄存器
	ChannelSel=0;
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ChannelSel;
}

/*----------------------------
ADC??????
----------------------------*/
void ADC_ISR() interrupt 5 using 1
{
	ADC_CONTR &= ~ADC_FLAG;  //FLAG位清零，以便再次产生中断请求   
	AD_Result[ChannelSel]=ADC_RES; //保存转换结果 
	ChannelSel=(ChannelSel+1)&0x07; //换到下一通道 
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ChannelSel;  //重置控制寄存器 
}

uint8_t ADC_Read(uint8_t Ch)
{
	return AD_Result[Ch];
}
