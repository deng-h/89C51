#include "OLED.h"
#include "charcode.h"

#include <STC15F2K60S2.h>
static void OLED_WriteDat(uint8 data_t);
static void OLED_WriteCmd(uint8 cmd);
static void OLED_SetPos(uint8 x, uint8 y);
static void OLED_PinInit(void);
static void OLED_DLY_ms(uint16 ms);

/*!
*  描述       OLED显示屏清屏函数
*  参数       NewState       0x00为关OLED，0x01为开OLED
*  示例:       OLED_Cmd (0x00);
*/
void OLED_Switch(char NewState)
{
  if(NewState != 0) NewState = 1;
  OLED_WriteCmd(0xAE | NewState);
}

/*!
*  @描述       OLED显示屏清屏函数
*  @参数       color       0x00为全暗，0xff为全亮
*  示例:       OLED_ClearScreen (0x00);
*/
void OLED_ClearScreen(uint8 color)
{
  uint16 y,x;	
  for(y=0; y < OLED_PAGE_MAX; y++)  //8页，每页128字节
  {
    OLED_WriteCmd(0xb0 + y);  //设置页地址
    OLED_WriteCmd(0x01);   //设置8位起始列地址的低四位
    OLED_WriteCmd(0x10);   //设置8位起始列地址的高四位
    for(x=0; x < OLED_X_MAX; x++)
      OLED_WriteDat(color);
  }
}

/*!
*  @描述       OLED初始化
*  示例:       OLED_Init ();
*/
void OLED_Init (void)
{
	P23=0;  //拉低,片选
  OLED_PinInit();
  
  OLED_SCLH;	
  OLED_RSTL; //初始化OLED
  
  OLED_DLY_ms(50);
  OLED_RSTH;
  
  OLED_Switch(0);//--turn off oled panel
  OLED_WriteCmd(0x00);//---set low column address
  OLED_WriteCmd(0x10);//---set high column address
  OLED_WriteCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WriteCmd(0x81);//--set contrast control register
  OLED_WriteCmd(0xcf); // Set SEG Output Current Brightness
  OLED_WriteCmd(0xa1);//--Set SEG/Column Mapping     //
  OLED_WriteCmd(0xc8);//Set COM/Row Scan Direction  //
  OLED_WriteCmd(0xa6);//--set normal display
  OLED_WriteCmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WriteCmd(0x3f);//--1/64 duty
  OLED_WriteCmd(0xd3);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WriteCmd(0x00);//-not offset
  OLED_WriteCmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WriteCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WriteCmd(0xd9);//--set pre-charge period
  OLED_WriteCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WriteCmd(0xda);//--set com pins hardware configuration
  OLED_WriteCmd(0x12);
  OLED_WriteCmd(0xdb);//--set vcomh
  OLED_WriteCmd(0x40);//Set VCOM Deselect Level
  OLED_WriteCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WriteCmd(0x02);//
  OLED_WriteCmd(0x8d);//--set Charge Pump enable/disable
  OLED_WriteCmd(0x14);//--set(0x10) disable
  OLED_WriteCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WriteCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_Switch(1);//--turn on oled panel
  OLED_ClearScreen(BLACK);
  OLED_SetPos(0, 0);
}

/*!
*  @描述       显示一个6x8的字符
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~7)
*  @参数       data1   待显示的字符
*  示例:       gpio_init (0, 0, 'H');    //在屏幕(0,0)位置显示 H
*/
void OLED_P6x8Char(uint8 x, uint8 y, char ch)
{
  uint8 c = 0, i = 0; 
  c =ch-32;
  if(x>126)
  {
    x=0;
    y++;
  }
  OLED_SetPos(x,y);    
  for(i=0;i<6;i++)
  {     
    OLED_WriteDat(F6x8[c][i]);  
  }
  x+=6;
}

/*!
*  @描述       显示一个6x8的字符串
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~7)
*  @参数       data1   待显示的字符串
*  示例:       gpio_init (0, 0, "HELLO");    //在屏幕(0,0)位置显示 HELLO
*/
void OLED_P6x8Str(uint8 x, uint8 y, const char *ch)
{
  uint8 c = 0, i = 0, j = 0;      
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126)
    {
      x=0;
      y++;
    }
    OLED_SetPos(x,y);    
    for(i=0;i<6;i++)
    {     
      OLED_WriteDat(F6x8[c][i]);  
    }
    x+=6;
    j++;
  }
}

/*!
*  @描述       显示一个6x8的整数数
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~7)
*  @参数       data1   待显示的整数
*  @参数       set     显示整数位位数，如果该参数带负号，则显示结果有符号
*  示例:       gpio_init (0, 0, 123, 4);    //在屏幕(0,0)位置显示 0123
               gpio_init (0, 0, -123, -3);    //在屏幕(0,0)位置显示 -123
*/
void OLED_P6x8Int(uint8 x, uint8 y, int16 data1, int8 set)
{
  uint8 result[7];
  if(data1<0)  //负数的情况
  {
    data1 *= -1;
    result[0] = '-';
  }
  else
  {
    result[0] = '+';
  }
  result[1] = (uint8)((data1%100000)/10000+48);
  result[2] = (uint8)((data1%10000)/1000+48);
  result[3] = (uint8)((data1%1000)/100+48);
  result[4] = (uint8)((data1%100)/10+48);
  result[5] = (uint8)(data1%10+48);
  result[6] = '\0';
  if(set < 0)
  {
    result[5 + set] = result[0];
    OLED_P6x8Str(x, y, (char *)&(result[5 + set]));
  }
  else if(set > 0)
  {
    OLED_P6x8Str(x, y, (char *)&(result[6 - set]));
  }
}

/*!
*  @描述       显示一个6x8的浮点数
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~7)
*  @参数       data1   待显示的浮点数
*  @参数       set     显示浮点数的整数位位数，如果该参数带负号，则显示结果有符号
*  示例:       gpio_init (0, 0, 100.0/3, 2);    //在屏幕(0,0)位置显示 33.33
               gpio_init (0, 0, 100.0/3, -2);    //在屏幕(0,0)位置显示 +33.33
*/
void OLED_P6x8Flo(uint8 x, uint8 y, float data1, int8 set)
{
  uint8 result[9];
  uint16 data2;
  if(data1<0)
  {			
    result[0] = '-';
    data1 *= -1;
  }
  else
  {
    result[0]='+';
  }
  data1 += 0.000001;
  data2 = (uint16)(data1*100);
  result[1] = (uint8)((data2%1000000)/100000+48);
  result[2] = (uint8)((data2%100000)/10000+48);
  result[3] = (uint8)((data2%10000)/1000+48);
  result[4] = (uint8)((data2%1000)/100+48);
  result[5] = '.';
  result[6] = (uint8)((data2%100)/10+48);
  result[7] = (uint8)(data2%10+48);
  result[8] = '\0';
  
  if(set < 0)
  {
    result[4 + set] = result[0];
    OLED_P6x8Str(x, y, (char *)&(result[4 + set]));
  }
  else if(set > 0)
  {
    OLED_P6x8Str(x, y, (char *)&(result[5 - set]));
  }
}

/*!
*  @描述       显示一个8x16的标准ASCII字符
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~6)
*  @参数       ch      待显示的字符
*  示例:       gpio_init (0, 0, 'H');    //在屏幕(0,0)位置显示 H
*/
void OLED_P8x16Char(uint8 x, uint8 y, char ch)
{
  uint8 c = 0, i = 0;
  
  c = ch - 32;
  if(x > 120)
  {
    x=0;
    y++;
  }
  OLED_SetPos(x,y);
  for(i=0;i<8;i++)
  {
    OLED_WriteDat(F8X16[c*16+i]);  //*16是因为一维数组
  }
  OLED_SetPos(x,y+1);
  for(i=0;i<8;i++)
  {
    OLED_WriteDat(F8X16[c*16+i+8]);
  }
  x+=8;
}

/*!
*  @描述       显示一个8x16的标准ASCII字符串
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~6)
*  @参数       ch      待显示的字符串
*  示例:       gpio_init (0, 0, "HELLO");    //在屏幕(0,0)位置显示 HELLO
*/
void OLED_P8x16Str(uint8 x, uint8 y, const char *ch)
{
  uint8 c = 0, i = 0, j = 0;
  while (ch[j] != '\0')
  {    
    c = ch[j] - 32;
    if(x > 120)
    {
      x=0;
      y++;
    }
    OLED_SetPos(x,y);
    for(i=0;i<8;i++)
    {
      OLED_WriteDat(F8X16[c*16+i]);
    }
    OLED_SetPos(x,y+1);
    for(i=0;i<8;i++)
    {
      OLED_WriteDat(F8X16[c*16+i+8]);
    }
    x+=8;
    j++;
  }
}

/*!
*  @描述       显示一个14x16的中文字符
*  @参数       x       显示位置的横坐标(0~127)
*  @参数       y       显示位置的纵坐标(0~6)
*  @参数       ch      待显示的字符串
*  示例:       gpio_init (0, 0, "你好");    //在屏幕(0,0)位置显示 你好
*  注意        显示汉字时需要用文字取模软件取模字体，取模时设置为 宋体五号，纵向取模，字节倒叙，再添加至charcode.h中的Word14x16数组中方可使用
*/
void OLED_P14x16CHCHAR(uint8 x, uint8 y, const char *ch)
{
  uint8 wordnum, i;
  while(*ch != '\0')
  {
    if(x > 114)
    {
      x = 0;
      ++ y;
    }
    OLED_SetPos(x, y);
    for(wordnum = 0; wordnum < sizeof(Word14x16)/31; ++wordnum)
    {
      if(((*ch & 0xff) == (Word14x16[wordnum].word_name[0] & 0xff)) && ((*(ch+1) & 0xff) == (Word14x16[wordnum].word_name[1] & 0xff)))
      {
        for(i=0; i<14; i++)
        {
          OLED_WriteDat(Word14x16[wordnum].index[i]);
        }
        OLED_SetPos(x, y+1);
        for(i=14; i<28; i++)
        {
          OLED_WriteDat(Word14x16[wordnum].index[i]);
        }
        x += 14;
        ch += 2;
        break;
      }
    }
  }
}

/*!
*  @描述       显示一个图片
*  @参数       x0      显示位置的起点横坐标(0~127)
*  @参数       y0      显示位置的起点纵坐标(0~7)
*  @参数       x1      显示位置的起点横坐标(0~127)
*  @参数       y1      显示位置的起点纵坐标(0~7)
*  @参数       bmp     待显示的图片
*  示例:       gpio_init (0, 0, 100， 6， bmp);    //在屏幕(0,0)位置显示一个大小为100 * 48 的图片
*  注意:       显示图片时需要用图像取模软件取模，取模时设置为 数据水平，字节垂直，单色，最大尺寸128 * 64，字节内像素数据反序
*/
void OLED_PrintBMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,const char bmp[])
{ 	
  uint16 temp=0;
  uint8 x,y;
  for(y = y0; y <= y1; ++y)
  {
    OLED_SetPos(x0,y);				
    for(x = x0; x <= x1; ++x)
    {      
      OLED_WriteDat(bmp[temp++]);	    	
    }
  }
}

/****************** 以下为内部函数，不可调用 ******************/
static void OLED_DLY_ms(uint16 ms)
{                         
  unsigned int a;
  while(ms)
  {
    a=222;
    while(a--);
    ms--;
  }
  return;
}

static void OLED_PinInit(void)
{
	
}

static void OLED_WriteDat(uint8 data_t)   //写数据
{
  uint8 temp = 8;
#ifdef USE_CS
  OLED_CSL;
#endif /* USE_CS */
  OLED_DCH;  //DC拉高，写数据
  OLED_SCLL;
  while (temp--)
  {
    if (data_t & 0x80)
    {
      OLED_SDAH;
    }
    else
    {
      OLED_SDAL;
    }
    OLED_SCLH;
    OLED_SCLL;
    data_t <<= 1;    
  }
#ifdef USE_CS
  OLED_CSH;
#endif /* USE_CS */
}
static void OLED_WriteCmd(uint8 cmd) //写命令
{
  uint8 temp = 8;
#ifdef USE_CS
  OLED_CSL;
#endif /* USE_CS */
  OLED_DCL;  //DC拉低，写命令
  OLED_SCLL;
  while (temp--)
  {
    if (cmd & 0x80)
    {
      OLED_SDAH;
    }
    else
    {
      OLED_SDAL;
    }
    OLED_SCLH;
    OLED_SCLL;
    cmd <<= 1;   
  }
#ifdef USE_CS
  OLED_CSH;
#endif /* USE_CS */
}

static void OLED_SetPos(uint8 x, uint8 y)//设置坐标
{ 
  OLED_WriteCmd(0xb0+y);
  OLED_WriteCmd(((x&0xf0)>>4)|0x10);
  OLED_WriteCmd((x&0x0f)|0x01); 
}