#include "STC15Fxxxx.h"
#include "stdint.h"


#define ADC_POWER 0x80     //ADC��Դ����λ
#define ADC_FLAG 0x10      //ADC��ɱ�־
#define ADC_START 0x08     //ADC����


#define ADC_SPEEDLL 0x00   //540��ʱ��
#define ADC_SPEEDL 0x20    //360��ʱ��
#define ADC_SPEEDH 0x40    //180��ʱ��
#define ADC_SPEEDHH 0x60   // 90��ʱ��

uint8_t ChannelSel;
uint8_t AD_Result[8];

void ADC_Init(void)
{
	P1ASF = 0xff;             //����P1��ΪADC����
	ADC_RES = 0;                    //�������Ĵ���
	ChannelSel=0;
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ChannelSel;
}

/*----------------------------
ADC??????
----------------------------*/
void ADC_ISR() interrupt 5 using 1
{
	ADC_CONTR &= ~ADC_FLAG;  //FLAGλ���㣬�Ա��ٴβ����ж�����   
	AD_Result[ChannelSel]=ADC_RES; //����ת����� 
	ChannelSel=(ChannelSel+1)&0x07; //������һͨ�� 
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ChannelSel;  //���ÿ��ƼĴ��� 
}

uint8_t ADC_Read(uint8_t Ch)
{
	return AD_Result[Ch];
}
