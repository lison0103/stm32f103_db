/*******************************************************************************
* File Name          : initial_devices.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains prototype of the devices initinal.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INITIAL_DEVICES_H
#define __INITIAL_DEVICES_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "delay.h"    
#include "led.h"
#include "input.h"
#include "can.h"
#include "ewdt.h"
#include "digital_led.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Initial_Device(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);



#endif  /* __INITIAL_DEVICES_H */


/******************************  END OF FILE  *********************************/





