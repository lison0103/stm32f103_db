/*******************************************************************************
* File Name          : can.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
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

u8 can1_receive = 0;


/*******************************************************************************
* Function Name  : CAN_Mode_Init
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
/** CAN init
tsjw:CAN_SJW_1tq~ CAN_SJW_4tq
tbs2:CAN_BS2_1tq~CAN_BS2_8tq;
tbs1:CAN_BS1_1tq ~CAN_BS1_16tq
brp:1~1024;  tq=(brp)*tpclk1
baud rate=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
mode:CAN_Mode_Normal;CAN_Mode_LoopBack;
if Fpclk is 36M,CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);
baud rate:36M/((8+9+1)*4)=500Kbps **/
u8 CAN_Mode_Init(CAN_TypeDef* CANx,u8 mode)
{ 
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PORTA时钟	                   											 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);			//初始化IO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);			//初始化IO
#endif
        
            //CAN单元设置
            CAN_DeInit(CANx);
            CAN_StructInit(&CAN_InitStructure);
            
            //CAN 
            CAN_InitStructure.CAN_TTCM=DISABLE;			  
            CAN_InitStructure.CAN_ABOM=DISABLE;				 
            CAN_InitStructure.CAN_AWUM=DISABLE;			
            CAN_InitStructure.CAN_NART=DISABLE;//ENABLE;			
            CAN_InitStructure.CAN_RFLM=DISABLE;		 	 
            CAN_InitStructure.CAN_TXFP=DISABLE;			
            CAN_InitStructure.CAN_Mode= mode;	                 
            //set baud rate
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
//            CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	//32??ID
//            CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//            CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32??MASK
//            CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
            
            //std id
//            CAN_FilterInitStructure.CAN_FilterIdHigh=(0x10) << 5;	//32??ID
//            CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//            CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32??MASK
//            CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xfffc;
            
            //ext id
            CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)0x1234<<3)&0xFFFF0000)>>16;	
            CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)0x1234<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;
            CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32 bit MASK
            CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xce8e;            
            CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
            CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;

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
* Function Name  : CAN1_RX0_IRQHandler
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
#if CAN1_RX0_INT_ENABLE	//使能RX0中断
			    
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
        
        /* DBL1 UP */
        if( kz_data_array[0] == 1 )
        {
            if( ( RxMessage.ExtId == 0x1234 ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                for( u8 i = 0; i < RxMessage.DLC; i++ )
                {
                    /* receive data */
//                    printf("CAN1_RX0[%d]:%d\r\n",i,RxMessage.Data[i]);
                }
            }
        }
        /* DBL1 UP */
        else if( kz_data_array[0] == 2 )
        {
            if( ( RxMessage.ExtId == 0x2345 ) && ( RxMessage.IDE == CAN_ID_EXT ) )
            {
                can1_receive = 1;        
                for( u8 i = 0; i < RxMessage.DLC; i++ )
                {
                    /* receive data */
//                    printf("CAN1_RX0[%d]:%d\r\n",i,RxMessage.Data[i]);
                }
            }
        }        
    }
}
#endif

			     

/*******************************************************************************
* Function Name  : Can_Send_Msg
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
/** CAN send data
len:data len(max len is 8)				     
msg:Data Pointer.
return:0,success;
**/		 
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
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
/** CAN receive data
buf:data cache;	 
return:0,no data receive;
other,Length of the received data;
**/
u8 Can_Receive_Msg(CAN_TypeDef* CANx,u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}


/******************************  END OF FILE  *********************************/












