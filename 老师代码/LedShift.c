#include "stdint.h"
#include "ledshift.h"

static uint8_t LedBit=0;
static uint8_t ShiftDir=LED_SHIFT_DIR_UP;
void LedShift(void)
{
	if(ShiftDir)
		LedBit--;
	else
		LedBit++;
	LedBit&=7;
	//LedBit=(LedBit+1)&0x07;
}

uint8_t GetLedBit(void)
{
	return LedBit;
}

void SetShiftDir(uint8_t Dir)
{
	ShiftDir=Dir;
}


