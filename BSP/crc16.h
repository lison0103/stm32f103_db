/*******************************************************************************
* File Name          : crc16.h
* Author             : lison
* Version            : V1.0
* Date               : 03/22/2016
* Description        : Contains the prototype of 16-bit CRC Calculation and verification.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRC16_H
#define __CRC16_H

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t MB_CRC16( uint8_t *pucFrame, uint16_t usLen );

#endif /* __CRC16_H */


/******************************  END OF FILE  *********************************/
