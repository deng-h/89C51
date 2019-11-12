#ifndef _PWM_H_
#define _PWM_H_
#include "STC15F2K60S2.h"

void PWM_Init(void);
void PWM_Out(unsigned char ch, unsigned char duty); //通道选择,占空比

#endif