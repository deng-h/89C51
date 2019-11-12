#ifndef _PWM_H_
#define _PWM_H_

#include "STDEF.h"

#define left 0
#define right 1

void PWM_INIT(void);
void PWM_Out(uchar channal , uchar duty);

#endif