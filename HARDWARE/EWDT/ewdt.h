
#ifndef __EWDT_H
#define __EWDT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define EWDT_TOOGLE() 	GPIOA->ODR ^= 0X0008

void power_on_bsp_check(void);
void EWDT_Drv_pin_config(void);


#endif //__EWDT_H