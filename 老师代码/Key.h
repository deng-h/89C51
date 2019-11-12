#ifndef _KEY_H_
#define _KEY_H_

#include "stdint.h"

void Key_Init(void);
void Key_Scan(void);
uint8_t Key_Read(void);

#endif

