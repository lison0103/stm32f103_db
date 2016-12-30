/*******************************************************************************
* File Name          : can.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : This file contains prototype of can functions.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H
#define __CAN_H	 

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define canbuffsize 120

#define CAN_FRAME_LEN   8
#define CAN_SEND_LEN    3*CAN_FRAME_LEN

#define CAN1_TEST_ID  0xfaf1
  
/* SF <-----> DBL1 */
#define CAN1RX_SF_ID  0xD0u
#define CAN1TX_DBL1_UPPER_ID  0xD1u
#define CAN1TX_DBL1_LOWER_ID  0xD2u
#define CAN1TX_DBL1_INTERM1_ID  0xD3u
#define CAN1TX_DBL1_INTERM2_ID  0xD4u

/* Exported functions ------------------------------------------------------- */
u8 CAN_Int_Init(CAN_TypeDef* CANx); 
u8 Can_Send_Msg(CAN_TypeDef* CANx,u32 exid,u8 msg[],u8 len);			
u8 Can_Receive_Msg(CAN_TypeDef* CANx,u8 buf[]);					
void Can_Receive_Data(void);

extern u16 g_u16CANSendFail;
extern u8 can1_receive;
	 										 							 				    				
#endif  /* __CAN_H */




/******************************  END OF FILE  *********************************/















