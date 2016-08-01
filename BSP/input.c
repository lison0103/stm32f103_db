/*******************************************************************************
* File Name          : input.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains input test function.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "input.h"
#include "led.h"
#include "digital_led.h"
#include "can.h"
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : ReadSwDp
* Description    : Read swdp data.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : swdp value.
*******************************************************************************/
u8 ReadSwDp(void)
{
    u8 swdp[4] = {0};
    u8 value;
    
    swdp[0] = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4);
    swdp[1] = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5);
    swdp[2] = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6);
    swdp[3] = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7);
    
    value = ( ((~swdp[3])&0x01) << 3 ) | ( ((~swdp[2])&0x01) << 2 ) | ( ((~swdp[1])&0x01) << 1 ) | ( ((~swdp[0])&0x01) << 0 );
    
    return   value;
}


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
             case 0x0: kz_data_array[0] = 0xfa;break;  
             case 0x2: kz_data_array[0] = 0x55;break; 
             case 0xa: kz_data_array[0] = 0xaa;break; 
             default:kz_data_array[0] = 0; 
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
     
    static u8 can1_comm_timeout = 0;
    u8 len = 0;
    
    if( can1_receive == 1 )
    {
        can1_receive = 0;
        can1_comm_timeout = 0;
    }
    else if( ++can1_comm_timeout >= 3 )
    {
        /*  can communication timeout process */
    }     
    
    len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);

    for( u8 i = 0; i < 20; i++ )
    {
        CAN1_TX_Data[i] = 0;
    }    
    
    for( u8 i = 4; i < 8; i++ )
    {
        CAN1_TX_Data[i] = EscRTBuff[i];
    }
    
    if( len > 0 )
    {
        CAN1_TX_Data[0] = CAN1_RX_Data[0];
        CAN1_TX_Data[1] = CAN1_RX_Data[1];
    }

    /* ESC ERROR CODE display */
    if( testmode == 0 )
    {
        dis_data[0] = 0;
        dis_data[1] = CAN1_RX_Data[2]/10;
        dis_data[2] = CAN1_RX_Data[2]%10;  
    }
    
    /* DBL1 UP */
    if( kz_data_array[0] == 0x55 )
    {
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_UP_ID, CAN1_TX_Data, 20);           
    }
    /* DBL1 DOWN */
    else if( kz_data_array[0] == 0xaa )
    {
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_DOWN_ID, CAN1_TX_Data, 20);
    }
    /* Test Mode */
    else if( testmode == 1 )
    {               
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_DOWN_ID, CAN1_TX_Data, 20);
    }		   

}

/******************************  END OF FILE  *********************************/




