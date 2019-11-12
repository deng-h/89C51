#include <REG51.H>
#include "stdint.h"
#include "ledshift.h"
//#include "key.h"

uint8_t Count=0;
void PeriodTask10ms(void)
{
	Led7Seg_Flush();
}

void PeriodTask1s(void)
{
	
}
void tm0_isr() interrupt 1 using 1
{
	PeriodTask10ms();
	if(Count++>=100)
	{
		Count=0;
		PeriodTask1s();
	}
}

