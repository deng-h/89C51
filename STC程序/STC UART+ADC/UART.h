#ifndef _UART_H_
#define _UART_H_

unsigned char UART_Read(unsigned char *Buf);
void UART_Write(unsigned char *Buf,unsigned char Num);  //写入数组函数  
void UART_Init(void); 
void UART_Write_byte(unsigned char dat);//写入单个字符函数
#endif