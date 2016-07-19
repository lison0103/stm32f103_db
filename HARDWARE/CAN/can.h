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
#include "sys.h"

/* Exported types ------------------------------------------------------------*/
typedef struct  {
  u8 sending;
  u8* p_CanBuff;
  s16 mlen;
  u8 tx_buff[200];
} CAN_TX_DATA_PROCESS_TypeDef;

typedef struct  {
  u8 recving;
  s16 rxcnt;
  s16 mlen;
  u8 data_packet;
  u8 recv_cnt;
  u8 recv_len;
  u8 rx_buff[200];
} CAN_RX_DATA_PROCESS_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define canbuffsize 120

#define CAN1TX_UP_ID    0x3456
#define CAN1RX_UP_ID    0x1234
#define CAN1TX_DOWN_ID  0x3488
#define CAN1RX_DOWN_ID  0x2345

/* Exported functions ------------------------------------------------------- */
u8 CAN_Int_Init(CAN_TypeDef* CANx); 
u8 Can_Send_Msg(CAN_TypeDef* CANx,u32 exid,u8* msg,u8 len);			
u8 Can_Receive_Msg(CAN_TypeDef* CANx,u8 *buf);					
void BSP_CAN_Send(CAN_TypeDef* CANx, CAN_TX_DATA_PROCESS_TypeDef* CanTx, uint32_t send_id, uint8_t *buff, uint32_t len);
uint32_t BSP_CAN_Receive(CAN_TypeDef* CANx,CAN_RX_DATA_PROCESS_TypeDef* CanRx, uint8_t *buff,uint32_t mlen);


/* CAN1 */
extern u8 CAN1_TX_Data[canbuffsize];
extern u8 CAN1_RX_Data[canbuffsize];

extern u8 can1_receive;

extern CAN_TX_DATA_PROCESS_TypeDef  CAN1_TX_UpDown;
extern CAN_RX_DATA_PROCESS_TypeDef  CAN1_RX_UpDown;
	 										 							 				    
				
#endif  /* __CAN_H */




/******************************  END OF FILE  *********************************/















