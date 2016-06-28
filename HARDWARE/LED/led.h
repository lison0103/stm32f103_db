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
#include "sys.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** LED Port **/
#define LED PBout(2)	

void LED_Init(void); 
 

#endif  /* _LED_H */


/******************************  END OF FILE  *********************************/


