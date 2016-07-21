/*******************************************************************************
* File Name          : can.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : This file contains can functions.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "can.h"
#include "led.h"
#include "delay.h"
#include "includes.h"
	 
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define CAN_BAUDRATE  1000      /* 1MBps   */
#define CAN_BAUDRATE  500  /* 500kBps */
//#define CAN_BAUDRATE  250  /* 250kBps */
//#define CAN_BAUDRATE  125  /* 125kBps */
//#define CAN_BAUDRATE  100  /* 100kBps */ 
//#define CAN_BAUDRATE  50   /* 50kBps  */ 
//#define CAN_BAUDRATE  20   /* 20kBps  */ 
//#define CAN_BAUDRATE  10   /* 10kBps  */

/* Private macro -------------------------------------------------------------*/
#define CAN1_RX0_INT_ENABLE	1		

#define CAN_FRAME_LEN   8
#define CAN_SEND_LEN    3*CAN_FRAME_LEN

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* CAN1 */
u8 CAN1_TX_Data[canbuffsize] = { 0 };
u8 CAN1_RX_Data[canbuffsize] = { 0 };

u8 can1_receive = 0;

CAN_TX_DATA_PROCESS_TypeDef  CAN1_TX_UpDown;
CAN_RX_DATA_PROCESS_TypeDef  CAN1_RX_UpDown;


/*******************************************************************************
* Function Name  : CAN_Int_Init
* Description    : Initialization can.
* CAN_SJW: CAN_SJW_1tq~ CAN_SJW_4tq
* CAN_BS2: CAN_BS2_1tq~CAN_BS2_8tq;
* CAN_BS1: CAN_BS1_1tq ~CAN_BS1_16tq
* CAN_Prescaler: 1~1024;  tq=(brp)*tpclk1
* baud rate = Fpclk1/((tbs1+1+tbs2+1+1)*brp)
* if Fpclk is 36M, baud rate:36M/((1+3+2)*24)=250Kbps               
* Input          : CANx: CAN1 or CAN2
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
u8 CAN_Int_Init(CAN_TypeDef* CANx)
{ 
        GPIO_InitTypeDef 		GPIO_InitStructure; 
        CAN_InitTypeDef        	        CAN_InitStructure;
        CAN_FilterInitTypeDef  	        CAN_FilterInitStructure;
#if CAN1_RX0_INT_ENABLE 
        NVIC_InitTypeDef  		NVIC_InitStructure;
#endif

#ifdef GEC_DBL1
        /* Enable GPIO clock */
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        
        /* Enable CAN clock */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

        /* Connect CAN pins to AF9 */
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_9);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_9); 
        
        /* Configure CAN RX and TX pins */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);        
        
#else
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	                   											 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
#endif
        
            
            CAN_DeInit(CANx);
            CAN_StructInit(&CAN_InitStructure);
            
            /*  non-time-triggered communication mode */
            CAN_InitStructure.CAN_TTCM=DISABLE;			
            /* automatic offline management software */
            CAN_InitStructure.CAN_ABOM=DISABLE;				 
            /* wake-sleep mode via software (Clear CAN-> MCR's SLEEP bit) */
            CAN_InitStructure.CAN_AWUM=DISABLE;			
            /* message is automatically transferred, in accordance with the CAN standard, */
            /* CAN hardware failure when sending packets would have been automatic retransmission until sent successfully */
            CAN_InitStructure.CAN_NART=DISABLE;//ENABLE;	
            /* message is not locked, the new over the old one */
            CAN_InitStructure.CAN_RFLM=DISABLE;		 	
            /* priority is determined by the packet identifier */
            CAN_InitStructure.CAN_TXFP=DISABLE;			
            CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	 
            
            /* set baud rate */
            CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  
            CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
            CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;   
            
#if CAN_BAUDRATE == 1000 /* 1MBps */
            CAN_InitStructure.CAN_Prescaler =6;
#elif CAN_BAUDRATE == 500 /* 500KBps */
            CAN_InitStructure.CAN_Prescaler =12;
#elif CAN_BAUDRATE == 250 /* 250KBps */
            CAN_InitStructure.CAN_Prescaler =24;
#elif CAN_BAUDRATE == 125 /* 125KBps */
            CAN_InitStructure.CAN_Prescaler =48;
#elif  CAN_BAUDRATE == 100 /* 100KBps */
            CAN_InitStructure.CAN_Prescaler =60;
#elif  CAN_BAUDRATE == 50 /* 50KBps */
            CAN_InitStructure.CAN_Prescaler =120;
#elif  CAN_BAUDRATE == 20 /* 20KBps */
            CAN_InitStructure.CAN_Prescaler =300;
#elif  CAN_BAUDRATE == 10 /* 10KBps */
            CAN_InitStructure.CAN_Prescaler =600;
#else
#error "Please select first the CAN Baudrate in Private defines "
#endif  /* CAN_BAUDRATE == 1000 */            
            
            /* Initializes the CAN1 */
            CAN_Init(CANx, &CAN_InitStructure);        	

            /* CAN1 filter init */
            CAN_FilterInitStructure.CAN_FilterNumber=0;	
            CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	
            CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	
            
            //any id
            CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	
            CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
            CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
            CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
            
            //std id
//            CAN_FilterInitStructure.CAN_FilterIdHigh=(0x10) << 5;	
//            CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//            CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;
//            CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xfffc;
            
            //ext id
//            CAN_FilterInitStructure.CAN_FilterIdHigh = (((u32)CAN1RX_UP_ID << 3) & 0xFFFF0000 ) >> 16;	
//            CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)CAN1RX_UP_ID << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;
//            CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) & 0xFFFF0000) >> 16;
//            CAN_FilterInitStructure.CAN_FilterMaskIdLow = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;  
            
            CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
            CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
            CAN_FilterInit(&CAN_FilterInitStructure);			           

#if CAN1_RX0_INT_ENABLE 
            /* IT Configuration for CAN1 */ 
            /* FIFO 0 message pending Interrupt ,full Interrupt , overrun Interrupt */
            CAN_ITConfig(CAN1,CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0, ENABLE); 		    
#ifdef GEC_DBL1
            NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
#else
            NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
#endif
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
}   

/*******************************************************************************
* Function Name  : CAN_RX_Process
* Description    : process the receive data.
*                  
* Input          : RxMessage: receive a CanRxMsg
*                  CanRx: define a CAN_RX_DATA_PROCESS_TypeDef struct to receive a frame data
* Output         : None
* Return         : None
*******************************************************************************/			    
void CAN_RX_Process( CanRxMsg RxMessage, CAN_RX_DATA_PROCESS_TypeDef* CanRx )
{
    
    u8 i;        
    
    if( ( CanRx->recving == 0 ) && ( RxMessage.Data[0] == 0xfa ) )
    {              
        CanRx->recv_len = RxMessage.Data[1] + 4;  
        CanRx->mlen = CanRx->recv_len;
        CanRx->rxcnt = 0;
        
        CanRx->recving = 1;
    }
    
    if( CanRx->recving == 1 )
    {
        
        for( i = 0; i < RxMessage.DLC; i++ )
        {
            /* receive data */
            CanRx->rx_buff[ CanRx->rxcnt++ ] = RxMessage.Data[i];
            
        }   
        CanRx->mlen -= RxMessage.DLC;    
        
        if( CanRx->mlen == 0 )            
        {
            CanRx->recving = 0;
            CanRx->data_packet = 1;  
        }
        else if( CanRx->mlen < 0 )
        {
            CanRx->recving = 0;
            CanRx->data_packet = 0;            
        }    
    }
    
}

/*******************************************************************************
* Function Name  : CAN1_RX0_IRQHandler
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
#if CAN1_RX0_INT_ENABLE	

#ifdef GEC_DBL1
void USB_LP_CAN1_RX0_IRQHandler(void)
#else
void CAN1_RX0_IRQHandler(void)
#endif
{
    CanRxMsg RxMessage;
    
    if( CAN_GetITStatus(CAN1,CAN_IT_FF0) != RESET)
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
    }
    else if( CAN_GetITStatus(CAN1,CAN_IT_FOV0) != RESET)
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_FOV0);
    }
    else
    {
        
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
        
        /* DBL1 UP */
        if( kz_data_array[0] == 0x55 )
        {
            if( ( RxMessage.ExtId == CAN1RX_UP_ID ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                
                CAN_RX_Process( RxMessage, &CAN1_RX_UpDown );
            }
        }
        /* DBL1 DOWN */
        else if( kz_data_array[0] == 0xaa )
        {
            if( ( RxMessage.ExtId == CAN1RX_DOWN_ID ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                
                CAN_RX_Process( RxMessage, &CAN1_RX_UpDown );
            }
        }
        /* Test Mode */
        else if( kz_data_array[0] == 0xfa )
        {
            if( ( RxMessage.ExtId == CAN1_TEST_ID ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                
                CAN_RX_Process( RxMessage, &CAN1_RX_UpDown );
            }            
        }
    }
}
#endif

/*******************************************************************************
* Function Name  : BSP_CAN_Send
* Description    : CAN send a frame data.
*                  
* Input          : CANx: CAN1 or CAN2
*                  CanRx: define a CAN_TX_DATA_PROCESS_TypeDef struct to send a frame data
*                  send_id: Extended identifier ID
*                  buff: send data address
*                  len: want to send data len
* Output         : None
* Return         : None
*******************************************************************************/  
void BSP_CAN_Send(CAN_TypeDef* CANx, CAN_TX_DATA_PROCESS_TypeDef* CanTx, uint32_t send_id, uint8_t *buff, uint32_t len)
{

        u32 i;
        u8  result = 0;	
        
        
        if( len > canbuffsize ) return;		
				
        /** packet the data pack ------------------------**/
        if( CanTx->sending == 0 && len > 0 )
        {
            CanTx->mlen = len + 4;
            
            CanTx->tx_buff[0] = 0xfa;
            CanTx->tx_buff[1] = CanTx->mlen - 4;
            for( u8 j = 0; j < CanTx->mlen - 4; j++ )
            {
                CanTx->tx_buff[j+2] = buff[j];
            }
            i = MB_CRC16( CanTx->tx_buff, CanTx->mlen - 2 );
            CanTx->tx_buff[CanTx->mlen - 2] = i;
            CanTx->tx_buff[CanTx->mlen - 1] = i>>8;    
            
            CanTx->p_CanBuff = &CanTx->tx_buff[0];
            CanTx->sending = 1;
        } 
        
        
        /** CAN1 send data ---------------------------------**/
        if( CanTx->sending == 1 )
        {
            
            if( CanTx->mlen > CAN_SEND_LEN )
            {
                for( i = 0; i < 3; i++ )
                {
                    result = Can_Send_Msg(CANx, send_id, CanTx->p_CanBuff, CAN_FRAME_LEN ); 
                    if( result != 1 )
                    {
                        CanTx->p_CanBuff += CAN_FRAME_LEN;
                        CanTx->mlen -= CAN_FRAME_LEN;
                    }
                    
                }
            }
            else
            {
                if( CanTx->mlen > 2*CAN_FRAME_LEN )
                {
                    for( i = 0; i < 2; i++ )
                    {
                        result = Can_Send_Msg(CANx, send_id, CanTx->p_CanBuff, CAN_FRAME_LEN ); 
                        if( result != 1 )
                        {
                            CanTx->p_CanBuff += CAN_FRAME_LEN;
                            CanTx->mlen -= CAN_FRAME_LEN;
                        }
                    }   
                }
                else if( CanTx->mlen > CAN_FRAME_LEN )
                {
                    
                    result = Can_Send_Msg(CANx, send_id, CanTx->p_CanBuff, CAN_FRAME_LEN ); 
                    if( result != 1 )
                    {
                        CanTx->p_CanBuff += CAN_FRAME_LEN;
                        CanTx->mlen -= CAN_FRAME_LEN;
                    }                                      
                }
                
                if( CanTx->mlen <= CAN_FRAME_LEN )
                {
                    result = Can_Send_Msg(CANx, send_id, CanTx->p_CanBuff, CanTx->mlen );
                    if( result != 1 )
                    {
                        CanTx->mlen = 0;
                        CanTx->sending = 0;
                    }
                }
                
            }
        } 
    
}		

/*******************************************************************************
* Function Name  : BSP_CAN_Receive
* Description    : CAN reveive a frame data.
*                  
* Input          : CANx: CAN1 or CAN2
*                  CanRx: define a CAN_RX_DATA_PROCESS_TypeDef struct to receive a frame data
*                  buff: receive data address
*                  mlen: want to receive data len
* Output         : None
* Return         : Length of the received data
*******************************************************************************/   
uint32_t BSP_CAN_Receive(CAN_TypeDef* CANx,CAN_RX_DATA_PROCESS_TypeDef* CanRx, uint8_t *buff,uint32_t mlen)
{
    uint8_t *pstr;
    uint32_t i=0,len=0;
	
    switch (*(uint32_t*)&CANx)
    {
       case CAN1_BASE:
                       
        /** receive a data packet **/
        if( CanRx->data_packet == 1 )
        {
            if(!MB_CRC16(CanRx->rx_buff, CanRx->recv_len))
            {          
                /* ok */
                pstr = &CanRx->rx_buff[2];					
                len = CanRx->recv_len - 4;
                CanRx->recv_len = 0;
            }
            else
            {
                /* fail */
                for( u8 i = 0; i < CanRx->recv_len; i++ )
                {
                    CanRx->rx_buff[i] = 0;
                }
            }
            CanRx->data_packet = 0;
        }                         
        break;	
    }	   
    
    if(mlen && (mlen<len))
    {
        len = mlen;
    }
    
    if(len>canbuffsize) len=0;
    
    for(i=0;i<len;i++)
    {
        buff[i] = pstr[i];
    }		
			
    return(len);
}

/*******************************************************************************
* Function Name  : Can_Send_Msg
* Description    : CAN send data
*                  
* Input          : len: data len(max len is 8)
*                  msg: Data Pointer.
*                  exid: Extended identifier ID.
*                  CANx: CAN1 or CAN2
* Output         : None
* Return         : 0: success
*                  1: fail, no send mailbox 
*******************************************************************************/		 
u8 Can_Send_Msg(CAN_TypeDef* CANx,u32 exid,u8* msg,u8 len)
{	
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x12;			// STD ID
	TxMessage.ExtId=exid;			// EXT ID 
//	TxMessage.IDE=CAN_Id_Standard; 	        
        TxMessage.IDE=CAN_Id_Extended; 	        
	TxMessage.RTR=CAN_RTR_Data;		
	TxMessage.DLC=len;			
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	if( CAN_TxStatus_NoMailBox == CAN_Transmit(CANx, &TxMessage) )
        {
            return 1;
        }
        
        return 0;
}


/*******************************************************************************
* Function Name  : Can_Receive_Msg
* Description    : CAN receive data                 
* Input          : buf:data cache
* Output         : None
* Return         : 0: no data receive; 
*                  other: Length of the received data;
*******************************************************************************/
u8 Can_Receive_Msg(CAN_TypeDef* CANx,u8 *buf)
{		   		   
      u32 i;
      CanRxMsg RxMessage;
      if( CAN_MessagePending(CANx,CAN_FIFO0)==0)return 0;		 
      
      CAN_Receive(CANx, CAN_FIFO0, &RxMessage);	
      for(i=0;i<8;i++)
      {
          buf[i]=RxMessage.Data[i];  
      }
      return RxMessage.DLC;	
}


/******************************  END OF FILE  *********************************/












