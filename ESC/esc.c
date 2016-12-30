/*******************************************************************************
* File Name          : esc.c
* Author             : lison
* Version            : V1.0
* Date               : 08/01/2016
* Description        : Contains esc function.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "esc.h"
#include "delay.h"
#include "led.h"
#include "digital_led.h"
#include "can.h"
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CAN_COMM_HAND_TIME      5000u

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Can_Send_Data_Process(void);
static void Can_Receive_Data_Process(void);

static u8 stat_u8CommTimeOutError = 0u;  
u8 g_u8DBL1ReceiveData = 0u;

/*******************************************************************************
* Function Name  : GetAdr
* Description    : Get the DBL1 up or down configuration.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void GetAdr(void)
{

  u8 adr_temp=0;
  static u8 adr_pre=0;
  static u16 adr_cnt=0;
  
  adr_temp = ReadSwDp();
  
  if(adr_temp == adr_pre)
  {
      if(adr_cnt>100)
      {  
          switch(adr_temp)
          {
             case 0x00u: EscData.SwdpAdr = DBL1_TEST_MODE;break;  
             case 0x01u: EscData.SwdpAdr = DBL1_UPPER_ADDR;break; 
             case 0x02u: EscData.SwdpAdr = DBL1_LOWER_ADDR;break; 
             case 0x04u: EscData.SwdpAdr = DBL1_INTERM1_ADDR;break; 
             case 0x08u: EscData.SwdpAdr = DBL1_INTERM2_ADDR;break;             
             default:EscData.SwdpAdr = 0; 
          }
      }
      else
      {
          adr_cnt++;
      }  
  }  
  else
  {
      adr_cnt = 0;
  }  
  
  adr_pre = adr_temp;
}

/*******************************************************************************
* Function Name  : esc_error_display
* Description    : esc error display
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void esc_error_display(void)
{
    if( stat_u8CommTimeOutError )
    {
        EscData.ErrorCode = 0u;
        g_u8LedFlash = 1u;       
    }
    else
    {
        g_u8LedFlash = 0u;    
    }
    
    if( testmode == 0 )
    {        
        if( EscData.ErrorCode )
        {
            if( EscData.ErrorCode <= 100u )
            {
                dis_data[0] = 10u;
                dis_data[1] = (EscData.ErrorCode - 1u)%100/10;
                dis_data[2] = (EscData.ErrorCode - 1u)%10;
            }
            else
            {
                dis_data[0] = (EscData.ErrorCode - 1u)/100;
                dis_data[1] = (EscData.ErrorCode - 1u)%100/10;
                dis_data[2] = (EscData.ErrorCode - 1u)%10;                    
            }
        }
        else
        {
            dis_data[0] = 0u;
            dis_data[1] = 0u;
            dis_data[2] = 0u;                
        }        
    }
}

/*******************************************************************************
* Function Name  : Can_Send_Data_Process
* Description    :                  
* Input          : None
* Output         : None
* Return         : None 
*******************************************************************************/
static void Can_Send_Data_Process(void)
{	
    u8 i,len;
    u8 result;
    u16 crc;
    
/*
0	0-7	LIFE SIGNAL	
1	0-7	INPUTS 1-8
2	0-7	INPUTS 9-16
3	0-7	INPUTS 17-24
4	0-7	INPUTS 25-32
5-6	0-15	CRC
7	0-7	NOT USED
*/    
    
    for( i = 0u; i < 4u; i++ )
    {
        EscDataToSafety[0][i+1] = EscData.DBLInputData[i];
    }

    len = 7u;
    crc = MB_CRC16( &EscDataToSafety[0][0], len - 2u );
    EscDataToSafety[0][len - 2u] = (u8)crc;
    EscDataToSafety[0][len - 1u] = (u8)(crc >> 8u);   
    
    /* DBL1 UP */
    if( EscData.SwdpAdr == DBL1_UPPER_ADDR )
    {       
        result = Can_Send_Msg(CAN1, CAN1TX_DBL1_UPPER_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
        if( result )
        {
            /* No mail box, send fail */
            g_u16CANSendFail |= 0x01u; 
            CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
        }          
    }
    /* DBL1 DOWN */
    else if( EscData.SwdpAdr == DBL1_LOWER_ADDR )
    {
        result = Can_Send_Msg(CAN1, CAN1TX_DBL1_LOWER_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
        if( result )
        {
            /* No mail box, send fail */
            g_u16CANSendFail |= 0x01u; 
            CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
        }
    }
    /* DBL1 INTERM1 */
    else if( EscData.SwdpAdr == DBL1_INTERM1_ADDR )
    {
        result = Can_Send_Msg(CAN1, CAN1TX_DBL1_INTERM1_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
        if( result )
        {
            /* No mail box, send fail */
            g_u16CANSendFail |= 0x01u; 
            CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
        }
    }
    /* DBL1 INTERM2 */
    else if( EscData.SwdpAdr == DBL1_INTERM2_ADDR )
    {
        result = Can_Send_Msg(CAN1, CAN1TX_DBL1_INTERM2_ID, &EscDataToSafety[0][0], CAN_FRAME_LEN ); 
        if( result )
        {
            /* No mail box, send fail */
            g_u16CANSendFail |= 0x01u; 
            CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
        }
    }    
    else
    {}    
}

/*******************************************************************************
* Function Name  : Can_Receive_Data_Process
* Description    :                  
* Input          : None
* Output         : None
* Return         : None 
*******************************************************************************/
static void Can_Receive_Data_Process(void)
{	
    u8 i,j;
    static u8 stat_u8SEQN = 0u;
    
/*
0	0-7	LIFE SIGNAL	
1	0-7	OUTPUTS DBL1 UPPER
2	0-7	OUTPUTS DBL1 	LOWER
3	0-7	OUTPUTS DBL1 INTERM. 1
4	0-7	OUTPUTS DBL1 INTERM. 2
5-6	0-15	CRC
7	0-7	NOT USED
*/   
    
    if( !MB_CRC16(&EscDataFromSafety[0][0], 7u) )
    {
        g_u8DBL1ReceiveData = 1u;
        
        /* for test */
        EscData.ErrorCode = *(u16*)&EscDataFromSafety[0][0];

       
        /* LIFE SIGNAL check */
        if( stat_u8SEQN != EscDataFromSafety[0][0] )
        {
            stat_u8SEQN = EscDataFromSafety[0][0];
        }
        else
        {
            /* error */
        }        
        
        /* DBL1 UP */
        if( EscData.SwdpAdr == DBL1_UPPER_ADDR )
        {       
            /*EscData.DBLOutputData = EscDataFromSafety[0][1];*/
        }       
        /* DBL1 DOWN */
        else if( EscData.SwdpAdr == DBL1_LOWER_ADDR )
        {
            EscData.DBLOutputData = EscDataFromSafety[0][2];
        }
        /* DBL1 INTERM1 */
        else if( EscData.SwdpAdr == DBL1_INTERM1_ADDR )
        {
            EscData.DBLOutputData = EscDataFromSafety[0][3];
        }
        /* DBL1 INTERM2 */
        else if( EscData.SwdpAdr == DBL1_INTERM2_ADDR )
        {
            EscData.DBLOutputData = EscDataFromSafety[0][4];
        }
        else
        {
            g_u8DBL1ReceiveData = 0u;
        }
    }
    else
    {
        /* data error */
        for( j = 0u; j < 3u; j++ )
        {
            for( i = 0u; i < 8u; i++ )
            {
                EscDataFromSafety[j][i] = 0u;
            }
        }
        EscData.ErrorCode = 0u;
        EscData.DBLOutputData = 0u;
    }
}

/*******************************************************************************
* Function Name  : Can_comm
* Description    : Can communication.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_Comm(void)
{	 
    static u8 stat_u8DBL1CommTimeout = 0u;   
    static u16 stat_u16TimerDBL1CommWait = 0u, stat_u16DBL1HandshakeSuccess = 0u;
    static u16 stat_u16TimeCan1Error = 0u;    
    
    /* comm timeout check */
    if( g_u8DBL1ReceiveData == 1 )
    {
        g_u8DBL1ReceiveData = 0;
        stat_u8DBL1CommTimeout = 0;
        stat_u16DBL1HandshakeSuccess = 1u;
        stat_u8CommTimeOutError = 0;  
    }
    else if( stat_u16DBL1HandshakeSuccess )
    {
        if( stat_u8DBL1CommTimeout < 0xffu )
        {
            stat_u8DBL1CommTimeout++;
        }
        if( stat_u8DBL1CommTimeout > 3u )
        {
            /*  can communication timeout process */
            stat_u8CommTimeOutError = 1u;       
        }
    }
    else
    {
        if( stat_u16TimerDBL1CommWait < 0xffffu )
        {
            stat_u16TimerDBL1CommWait++;
        }
        if( stat_u16TimerDBL1CommWait * 10u > CAN_COMM_HAND_TIME )
        {
            /*  can communication handshake timeout when power on */
            stat_u8CommTimeOutError = 1u;         
        }            
    }

    /* Receive data from SF */
    if( can1_receive == 1u )
    {
        can1_receive = 0u;
        stat_u16TimeCan1Error = 0u;
        Can_Receive_Data();    
        Can_Receive_Data_Process();
    }
    else
    {    
        /* CAN error check */            
        if( stat_u16TimeCan1Error < 0xffffu )
        {
            stat_u16TimeCan1Error++;
        }
        
        /* 1000ms */
        if( stat_u16TimeCan1Error > 100u )
        {
            stat_u16TimeCan1Error = 0u;
            if( CAN1->ESR & CAN_ESR_BOFF )
            {
                CAN_Int_Init(CAN1);
            }                    
            
        }
    }
    
    /* Send data to SF */
    Can_Send_Data_Process();
        
}



/******************************  END OF FILE  *********************************/




