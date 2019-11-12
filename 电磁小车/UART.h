#ifndef _UART_H_
#define _UART_H_
#include "STDEF.h"

void UART_Write(uchar *BUF, uchar NUM);
void UART_Write_Byte(uchar byte);
//void UART_HEX2TXT(uchar NUM);

void UART_INIT(void);
	
uchar UART_Read(uchar *BUF);


#endif