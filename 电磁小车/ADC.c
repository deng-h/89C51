#include "STC15Fxxxx.h"
#include "STDEF.h"


#define ADC_Power 0x80     //ADC��Դ����λ
#define ADC_Flag 0x10      //ADC��ɱ�־
#define ADC_Start 0x08     //ADC����


#define ADC_Speed_LL 0x00   //540��ʱ��
#define ADC_Speed_L 0x20    //360��ʱ��
#define ADC_Speed_H 0x40    //180��ʱ��
#define ADC_Speed_HH 0x60   // 90��ʱ��

uchar Channel_Sel;
uchar AD_Result[8];

void ADC_INIT(void)
{
	P1ASF = 0xFF;             //����P1��ΪADC����
	ADC_RES = 0;                    //�������Ĵ���
	Channel_Sel=0;
	ADC_CONTR = ADC_Power | ADC_Speed_LL | ADC_Start | Channel_Sel;
}

/*----------------------------
ADC�ж�
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
