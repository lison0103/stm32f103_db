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
    
    value = swdp[3] << 3 | swdp[2] << 2 | swdp[1] << 1 | swdp[0] << 0;
    
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
        case 0x5: kz_data_array[0] = 1;break; 
        case 0xa: kz_data_array[0] = 2;break; 
        case 0xf: kz_data_array[0] = 0;break; 
        default:kz_data_array[0] = 3; 
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



/******************************  END OF FILE  *********************************/



