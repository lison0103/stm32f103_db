#ifndef _LED_H
#define _LED_H
#include "sys.h"


//LED�˿ڶ���

#define LED PBout(2)	// PB2

void LED_Init(void); //��ʼ��
void SW_DP_Init(void);
u8 ReadSwDp(void);
 
#endif
