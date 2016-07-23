/*******************************************************************************
* File Name          : sys.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains get the DBL1 adr function.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
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
* Function Name  : HardwareTEST
* Description    : Test the board.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void HardwareTEST(void)
{
    u8 testdata[10];
    u8 testerror = 0;
    u8 len = 0;
    u16 waittms = 0;
    
    if( ReadSwDp() == 0x00 )
    {
        kz_data_array[0] = 0xfa;
    }
    
    CAN1_TX_Data[0] = 0xf1;
    testdata[0] = 0xf1;
    for( u8 i = 1; i < 10 ; i++ )
    {
        CAN1_TX_Data[i] = i + 0xa0;
        testdata[i] = i + 0xa0;
    }
    BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1_TEST_ID, CAN1_TX_Data, 10);
    
    do
    {
        len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);
        delay_ms(1);
        EWDT_TOOGLE();
        waittms++;
        if( waittms > 5000 )
        {
            waittms = 0;
            break;
        }
    }
    while( len != 10 || CAN1_RX_Data[0] != 0xf1 );     
    
    if( len == 10 && CAN1_RX_Data[0] == 0xf1 )
    {
        waittms = 0;
        for( u8 i = 2; i < 10 ; i++ )
        {
            CAN1_TX_Data[i] = CAN1_RX_Data[i];
        }
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1_TEST_ID, CAN1_TX_Data, 10);
        
        do
        {
            len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);
            delay_ms(1);
            EWDT_TOOGLE();
            waittms++;
            if( waittms > 5000 )
            {
                waittms = 0;
                break;
            }
        }
        while( len != 10 || CAN1_RX_Data[0] != 0xf1 ); 
        
        if( len == 10 && CAN1_RX_Data[0] == 0xf1 )
        {
            for( u8 i = 2; i < 10 ; i++ )
            {
                if( CAN1_RX_Data[i] != testdata[i] )
                {
                    testerror = 1;
                    break;
                }
            }
            
            if( testerror == 0 )
            {
                if( CAN1_RX_Data[1] == 0xb1 )
                {
                    testmode = 1;
                }               
            }
        } 
        
        
    }
    else
    {
        CAN_FilterInitTypeDef  	        CAN_FilterInitStructure;
        /* CAN1 filter init */
        CAN_FilterInitStructure.CAN_FilterNumber=0;	
        CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	
        CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	
        
        CAN_FilterInitStructure.CAN_FilterIdHigh = (((u32)CAN1RX_UP_ID << 3) & 0xFFFF0000 ) >> 16;	
        CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)CAN1RX_UP_ID << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;
        CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) & 0xFFFF0000) >> 16;
        CAN_FilterInitStructure.CAN_FilterMaskIdLow = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;  
        
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
        CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
        CAN_FilterInit(&CAN_FilterInitStructure);          
    }
}


/******************************  END OF FILE  *********************************/



