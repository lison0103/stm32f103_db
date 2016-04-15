/*******************************************************************************
* File Name          : initial_devices.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INITIAL_DEVICES_H
#define __INITIAL_DEVICES_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "delay.h"    
#include "led.h"
#include "hw_test.h"
#include "can.h"
#include "ewdt.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Bsp_Init(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);



#endif  /* __INITIAL_DEVICES_H */


/******************************  END OF FILE  *********************************/





