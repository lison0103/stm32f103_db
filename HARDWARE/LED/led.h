#ifndef _LED_H
#define _LED_H
#include "sys.h"


//LED端口定义

#define LED PBout(2)	// PB2

void LED_Init(void); //初始化
void SW_DP_Init(void);
u8 ReadSwDp(void);
 
#endif
