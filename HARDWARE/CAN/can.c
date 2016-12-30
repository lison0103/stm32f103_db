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
#include "esc.h"	 
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define CAN_BAUDRATE  1000      /* 1MBps   */
//#define CAN_BAUDRATE  500  /* 500kBps */
#define CAN_BAUDRATE  250  /* 250kBps */
//#define CAN_BAUDRATE  125  /* 125kBps */
//#define CAN_BAUDRATE  100  /* 100kBps */ 
//#define CAN_BAUDRATE  50   /* 50kBps  */ 
//#define CAN_BAUDRATE  20   /* 20kBps  */ 
//#define CAN_BAUDRATE  10   /* 10kBps  */

/* Private macro -------------------------------------------------------------*/
#define CAN1_RX0_INT_ENABLE	1		

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Can_Receive_Buffer(u8 rxmsg[], u16 canid);


u8 can1_receive = 0;

u16 g_u16CANSendFail = 0u;

/* Esc receive data buffer */
u8 EscDataFromSafetyBuffer[3][8];

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
        
            
            CAN_DeInit(CANx);
            CAN_StructInit(&CAN_InitStructure);
            
            /*  non-time-triggered communication mode */
            CAN_InitStructure.CAN_TTCM=DISABLE;			
            /* automatic offline management software */
            CAN_InitStructure.CAN_ABOM=ENABLE;				 
            /* wake-sleep mode via software (Clear CAN-> MCR's SLEEP bit) */
            CAN_InitStructure.CAN_AWUM=ENABLE;			
            /* message is automatically transferred, in accordance with the CAN standard, */
            /* CAN hardware failure when sending packets would have been automatic retransmission until sent successfully */
            CAN_InitStructure.CAN_NART=DISABLE;//ENABLE;	
            /* message is not locked, the new over the old one */
            CAN_InitStructure.CAN_RFLM=DISABLE;		 	
            /* priority is determined by the packet identifier */
            CAN_InitStructure.CAN_TXFP=ENABLE;			
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
            CAN_ITConfig(CAN1,CAN_IT_FMP0 , ENABLE); 		    
            CAN_ITConfig(CAN1,CAN_IT_FF0, ENABLE); 		    
            CAN_ITConfig(CAN1,CAN_IT_FOV0, ENABLE);		    

            NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&NVIC_InitStructure);
#endif
            CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);                
            /* Enable CAN1 TX0 interrupt IRQ channel */
            NVIC_InitStructure.NVIC_IRQChannel = (u8)CAN1_TX_IRQn;
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1u;
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1u;
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&NVIC_InitStructure);    
            
            return 0;
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

void USB_LP_CAN1_RX0_IRQHandler(void)
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
        
        /** SF data RECEIVE **/
        if(( RxMessage.ExtId >= CAN1RX_SF_ID ) && ( RxMessage.ExtId <= CAN1RX_SF_ID ))
        {
            if( ( RxMessage.DLC == CAN_FRAME_LEN ) && ( RxMessage.IDE == CAN_ID_EXT ))
            {
                can1_receive = 1;            
                Can_Receive_Buffer(RxMessage.Data, (u16)RxMessage.ExtId);
            }
        }   
        /* Test Mode */
        else if( EscData.SwdpAdr == DBL1_TEST_MODE )
        {
            if( ( RxMessage.ExtId == CAN1_TEST_ID ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                
                Can_Receive_Buffer(RxMessage.Data, (u16)RxMessage.ExtId);
            }            
        }
        else
        {}
    }
}
#endif

/*******************************************************************************
* Function Name  : CAN1_TX_IRQHandler
* Description    : This function handles CAN1 TX interrupt request.               
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/  
void CAN1_TX_IRQHandler(void)
{
    u8 result;
    
    CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP0);
    CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);
    
    /* DBL1 UP */
    if( EscData.SwdpAdr == DBL1_UPPER_ADDR )
    {       
        if( g_u16CANSendFail & 0x01u )
        {
            result = Can_Send_Msg(CAN1, CAN1TX_DBL1_UPPER_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
            if( result )
            {
                /* No mail box, send fail */
                g_u16CANSendFail |= 0x01u; 
                CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
            }   
            else
            {
                g_u16CANSendFail &= ~0x01u; 
            }
        }
    }
    /* DBL1 DOWN */
    else if( EscData.SwdpAdr == DBL1_LOWER_ADDR )
    {
        if( g_u16CANSendFail & 0x01u )
        {
            result = Can_Send_Msg(CAN1, CAN1TX_DBL1_LOWER_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
            if( result )
            {
                /* No mail box, send fail */
                g_u16CANSendFail |= 0x01u; 
                CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
            }
            else
            {
                g_u16CANSendFail &= ~0x01u; 
            }
        }
    }
    /* DBL1 INTERM1 */
    else if( EscData.SwdpAdr == DBL1_INTERM1_ADDR )
    {
        if( g_u16CANSendFail & 0x01u )
        {
            result = Can_Send_Msg(CAN1, CAN1TX_DBL1_INTERM1_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
            if( result )
            {
                /* No mail box, send fail */
                g_u16CANSendFail |= 0x01u; 
                CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
            }
            else
            {
                g_u16CANSendFail &= ~0x01u; 
            }
        }
    }
    /* DBL1 INTERM2 */
    else if( EscData.SwdpAdr == DBL1_INTERM2_ADDR )
    {
        if( g_u16CANSendFail & 0x01u )
        {
            result = Can_Send_Msg(CAN1, CAN1TX_DBL1_INTERM2_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
            if( result )
            {
                /* No mail box, send fail */
                g_u16CANSendFail |= 0x01u; 
                CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
            }
            else
            {
                g_u16CANSendFail &= ~0x01u; 
            }
        }
    }    
    else
    {}      
    
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
u8 Can_Send_Msg(CAN_TypeDef* CANx,u32 exid,u8 msg[],u8 len)
{	
	u16 i = 0u;
        u8 result = 0u;        
	CanTxMsg TxMessage;
        
	TxMessage.StdId = 0x12u;			
	TxMessage.ExtId = exid;			
/*	TxMessage.IDE = CAN_Id_Standard; */
        TxMessage.IDE = CAN_Id_Extended; 	        
	TxMessage.RTR = CAN_RTR_Data;		
	TxMessage.DLC = len;			
	for(i = 0u; i < len; i++)
        {
          TxMessage.Data[i] = msg[i];
        }
	if( CAN_TxStatus_NoMailBox == CAN_Transmit(CANx, &TxMessage) )
        {
            result =  1u;
        }
        else
        {
            result =  0u;
        }
        
        return result;
}


/*******************************************************************************
* Function Name  : Can_Receive_Msg
* Description    : CAN receive data                 
* Input          : buf:data cache
* Output         : None
* Return         : 0: no data receive; 
*                  other: Length of the received data;
*******************************************************************************/
u8 Can_Receive_Msg(CAN_TypeDef* CANx,u8 buf[])
{		   		   
      u32 i;
      u8 result = 0u; 
      CanRxMsg RxMessage;
      
      if( CAN_MessagePending(CANx,CAN_FIFO0)== 0u )
      {
          result =  0u;		 
      }  
      else
      {          
          CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
          
          for(i = 0u; i < RxMessage.DLC; i++)
          {
              buf[i] = RxMessage.Data[i];  
          }
          
          result = RxMessage.DLC;
      }
      return result;	
}


/*******************************************************************************
* Function Name  : Can_Receive_Buffer
* Description    :                  
* Input          : None
* Output         : None
* Return         : None 
*******************************************************************************/
static void Can_Receive_Buffer(u8 rxmsg[], u16 canid)
{	  
    u8 i;

    for( i = 0u; i < 8u; i++ )
    {
        EscDataFromSafetyBuffer[canid - CAN1RX_SF_ID][i] = rxmsg[i];
    }
}

/*******************************************************************************
* Function Name  : Can_Receive_Data
* Description    :                 
* Input          : None 
* Output         : None
* Return         : None 
*******************************************************************************/
void Can_Receive_Data(void)
{	  
    u8 i,j;
    
    for( j = 0u; j < 3u; j++ )
    {
        for( i = 0u; i < 8u; i++ )
        {
            EscDataFromSafety[j][i] = EscDataFromSafetyBuffer[j][i];
        }  
    }
}

/******************************  END OF FILE  *********************************/












