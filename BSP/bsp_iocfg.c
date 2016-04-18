/*******************************************************************************
* File Name          : bsp_iocfg.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*                      
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_iocfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/*******************************************************************************
* Function Name  : Input_Output_PinInit
* Description    : Initializes the Input and Output GPIO
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Input_Output_PinInit(void)
{
  
#ifdef GEC_DBL1
      GPIO_InitTypeDef GPIO_InitStruct;
          
      /* Enable GPIO clock */
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE, ENABLE);
      
      //input
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;             
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;       
      GPIO_Init(GPIOA , &GPIO_InitStruct);    
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOB , &GPIO_InitStruct);        

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;                  
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;                  
      GPIO_Init(GPIOE , &GPIO_InitStruct);   
      
      //output
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
            
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
      GPIO_Init(GPIOB , &GPIO_InitStruct);  
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
      GPIO_Init(GPIOE , &GPIO_InitStruct);      
      
#else    
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE );
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
  
      GPIO_InitTypeDef GPIO_InitStruct;

      //input
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;             
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;       
      GPIO_Init(GPIOA , &GPIO_InitStruct);    
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOB , &GPIO_InitStruct);        

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;                  
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;                  
      GPIO_Init(GPIOE , &GPIO_InitStruct);        
      
      //output
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
            
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
      GPIO_Init(GPIOB , &GPIO_InitStruct);  
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
      GPIO_Init(GPIOE , &GPIO_InitStruct);  
#endif    

      OCP1 = 0;
      OCP2 = 0;
      OCP3 = 0;
      OCP4 = 0;
      OCP5 = 0;
      
      OTP1 = 0;
      OTP2 = 0;
      OTP3 = 0;      
}

/*******************************************************************************
* Function Name  : SW_DP_Init
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
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



/******************************  END OF FILE  *********************************/


