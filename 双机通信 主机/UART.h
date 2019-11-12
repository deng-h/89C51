
//UART驱动代码.h文件

#ifndef __UART_H__
#define __UART_H__
#include <reg52.h>
void Uart_init();     //异步通信初始化
void Ex0_send();      //发送中断
void Uart_receive();  //接收通信中断
void delay(int i);    //延时函数
#endif
