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
#ifdef GEC_DBL1
#include "stm32f30x.h"
#else
#include "stm32f10x.h"
#endif
#include "hw_test.h"
#include "delay.h"    
#include "led.h"  
#include "digital_led.h"
#include "ewdt.h"
#include "crc16.h"
#include "can.h"
#include "input.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern u8 dis_data[3];
extern u8 kz_data_array[30];
extern u8 EscRTBuff[100]; 
extern u8 testmode;

#endif /* __INCLUDES_H */


/******************************  END OF FILE  *********************************/   

