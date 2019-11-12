#ifndef _UART_H_
#define _UART_H_
#include "stdint.h"

uint8_t UART_Read(uint8_t *Buf);
void UART_Write(uint8_t *Buf,uint8_t Num);
void UART_Init(void); 

#endif