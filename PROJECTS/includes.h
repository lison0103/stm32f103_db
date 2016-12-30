/*******************************************************************************
* File Name          : includes.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "bsp_iocfg.h"
#include "hw_test.h"
#include "delay.h"    
#include "led.h"  
#include "digital_led.h"
#include "ewdt.h"
#include "crc16.h"
#include "can.h"
#include "esc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern u8 dis_data[3];
extern u8 testmode;

#endif /* __INCLUDES_H */


/******************************  END OF FILE  *********************************/   

