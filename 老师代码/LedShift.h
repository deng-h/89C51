#ifndef _LEDSHIFT_H_
#define _LEDSHIFT_H_

#include "stdint.h"

#define LED_SHIFT_DIR_UP    0
#define LED_SHIFT_DIR_DOWN  1




uint8_t GetLedBit(void);
void LedShift(void);
void SetShiftDir(uint8_t Dir);






#endif

