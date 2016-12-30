/*******************************************************************************
* File Name          : can.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : This file contains prototype of the external watchdog functions.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EWDT_H
#define __EWDT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define EWDT_TOOGLE() 	GPIOA->ODR ^= 0X0008

void ExtWdtCheck(void);
void EWDT_Drv_pin_config(void);


#endif //__EWDT_H