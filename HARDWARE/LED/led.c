/*******************************************************************************
* File Name          : led.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : LED_Init
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void LED_Init(void)
{
 
#ifdef GEC_DBL1
      GPIO_InitTypeDef GPIO_InitStructure;
          
      /* Enable GPIO clock */
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
      
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
      GPIO_Init(GPIOB, &GPIO_InitStructure);               
      
#else
     GPIO_InitTypeDef  GPIO_InitStructure;
            
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
            
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED1-->PB.2 端口配置
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
     GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.2
     
     
#endif
     
     GPIO_SetBits(GPIOB,GPIO_Pin_2);						 //PB.2 输出高

}

 
void SW_DP_Init(void)
{
    
#ifdef GEC_DBL1
      GPIO_InitTypeDef GPIO_InitStructure;
          
      /* Enable GPIO clock */
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
      
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
      GPIO_Init(GPIOD, &GPIO_InitStructure);               
      
#else
      
      GPIO_InitTypeDef  GPIO_InitStructure;
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PD端口时钟
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;				 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
      GPIO_Init(GPIOD, &GPIO_InitStructure);			
#endif   
   
}


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

/******************************  END OF FILE  *********************************/