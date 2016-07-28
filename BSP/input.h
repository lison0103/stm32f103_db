/*******************************************************************************
* File Name          : input.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains prototype of input test function.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INPUT_H
#define __INPUT_H

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "bsp_iocfg.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CAN_Comm(void);
void GetAdr(void);
u8 ReadSwDp(void);


#endif  /* __INPUT_H */


/******************************  END OF FILE  *********************************/



