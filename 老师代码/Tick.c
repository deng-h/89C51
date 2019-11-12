#include "STC15Fxxxx.h"
#include "stdint.h"
#include "ledshift.h"
#include "task.h"

#define T5MS (65536-MAIN_Fosc*5/1000/12)     //12Tģʽ��5ms��ʱ


void Tick_Init(void)
{
	TMOD &= 0x0F;        //��ʽ0
	TL1 = (uint8_t)T5MS;        //??????
	TH1 = (uint8_t)(T5MS>>8);
	TR1 = 1; //???0????
	ET1 = 1; //?????0??
}

uint8_t Count=0;

void tm1_isr() interrupt 3 using 1
{
	PeriodTask5ms();
	if(Count++>=200)
	{
		Count=0;
		PeriodTask1s();
	}
}

