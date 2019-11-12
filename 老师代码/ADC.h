#ifndef _ADC_H_
#define _ADC_H_

#include "stdint.h"

void ADC_Init(void);
uint8_t ADC_Read(uint8_t Ch);

#endif