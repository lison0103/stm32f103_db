/*******************************************************************************
* File Name          : led.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : The file contains prototype of led functions.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LED_H
#define _LED_H

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** LED Port **/
#define LED_ON()   GPIO_ResetBits(GPIOB,GPIO_Pin_2)	
#define LED_OFF()   GPIO_SetBits(GPIOB,GPIO_Pin_2)	
#define LED_FLASH()   GPIOB->ODR ^= 0X0004

void LED_Init(void); 
 

#endif  /* _LED_H */


/******************************  END OF FILE  *********************************/


