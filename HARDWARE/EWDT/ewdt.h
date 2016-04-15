/*******************************************************************************
* File Name          : can.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EWDT_H
#define __EWDT_H

/* Includes ------------------------------------------------------------------*/
#ifdef GEC_DBL1
#include "stm32f30x.h"
#else
#include "stm32f10x.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define EWDT_TOOGLE() 	GPIOA->ODR ^= 0X0008

void power_on_bsp_check(void);
void EWDT_Drv_pin_config(void);


#endif //__EWDT_H