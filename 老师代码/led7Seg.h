#ifndef _LED7SEG_H_
#define _LED7SEG_H_

void Led7Seg_Flush(void);
void Led7Seg_WriteNum(uint8_t * NumBuf);
void Led7Seg_WriteCode(uint8_t * CodeBuf);

#define SEG7_O 16
#define SEG7_N 17
#define SEG7_SPACE 18

#endif