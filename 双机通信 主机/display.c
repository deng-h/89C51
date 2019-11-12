
//数码管驱动.c文件

#include <reg52.h>
#include "display.h"
char list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int count=1;
	void display()
{
	switch(count)
	{
		case 0:P0=list[0];break;
		case 1:P0=list[1];break;
		case 2:P0=list[2];break;
		case 3:P0=list[3];break;
		case 4:P0=list[4];break;
		case 5:P0=list[5];break;
		case 6:P0=list[6];break;
		case 7:P0=list[7];break;
		case 8:P0=list[8];break;
		case 9:P0=list[9];break;
	}
	count++;
	if (count==10) count=0;
}

