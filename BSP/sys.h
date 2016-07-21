/*******************************************************************************
* File Name          : sys.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains prototype of get the DBL1 adr function.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_H
#define __SYS_H	

/* Includes ------------------------------------------------------------------*/
#ifdef GEC_DBL1
#include "stm32f30x.h"
#else
#include "stm32f10x.h"
#endif


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GetAdr(void);
u8 ReadSwDp(void);
void HardwareTEST(void);

#endif  /* __SYS_H */


/******************************  END OF FILE  *********************************/







