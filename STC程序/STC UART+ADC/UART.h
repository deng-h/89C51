#ifndef _UART_H_
#define _UART_H_

unsigned char UART_Read(unsigned char *Buf);
void UART_Write(unsigned char *Buf,unsigned char Num);  //д�����麯��  
void UART_Init(void); 
void UART_Write_byte(unsigned char dat);//д�뵥���ַ�����
#endif