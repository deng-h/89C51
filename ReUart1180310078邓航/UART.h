#ifndef _UART_H_
#define _UART_H_

unsigned char UART_Read(unsigned char *Buf);
void UART_Write(unsigned char *Buf,unsigned char Num);
void UART_Init(void); 

#endif