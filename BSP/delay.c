/*******************************************************************************
* File Name          : delay.c
* Author             : lison
* Version            : V1.0
* Date               : 03/22/2016
* Description        : Contains the timing delays.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "timer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define  USE_SYSTICK_DELAY   0
#define  USE_TIM_DELAY       1

/* Private variables ---------------------------------------------------------*/
#if USE_SYSTICK_DELAY
static u8  fac_us=0;
static u16 fac_ms=0;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/	 
	 


#if USE_SYSTICK_DELAY

/*******************************************************************************
* Function Name  : Delay_Init
* Description    : Delay is managed using SysTick
*                  Initialization delay function
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_Init(void)	 
{
  
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us=SystemCoreClock/8000000;	 
	 
	fac_ms=(u16)fac_us*1000;   
}	

/*******************************************************************************
* Function Name  : delay_us
* Description    : delay nus
*                  
* Input          : nus: Number of us want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 temp;
        
        if(nus != 0)
        {
            SysTick->LOAD=nus*fac_us; 	  		 
            SysTick->VAL=0x00;        
            SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          	 
            do
            {
                    temp=SysTick->CTRL;
            }
            while(temp&0x01&&!(temp&(1<<16)));   
            SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       
            SysTick->VAL =0X00;       
        }
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : delay nms
*                  
* Input          : nms: Number of ms want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void delay_ms(u16 nms)
{	 		  	  
        u32 temp;
        u32 Count_H = 0,Count_L = 0;
        
        if(nms != 0)
        {                
            Count_H = nms/1864;
            Count_L = nms%1864;
                   
            Count_H ++;
            while(Count_H--)
            {
                if(Count_H > 0)nms = 1864;
                else nms = Count_L;
                
                SysTick->LOAD=(u32)nms*fac_ms;
                SysTick->VAL =0x00;           
                SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          
                do
                {
                  temp=SysTick->CTRL;
                }
                while(temp&0x01&&!(temp&(1<<16)));   
                SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       
                SysTick->VAL =0X00;      	  	    
            }
        }
} 

#elif USE_TIM_DELAY

/*******************************************************************************
* Function Name  : Delay_Init
* Description    : Delay is managed using TIM
*                  Initialization delay function
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_Init(void)	 
{
    TIM1_Int_Init(65535, 71);
}	

/*******************************************************************************
* Function Name  : delay_us
* Description    : delay nus
*                  
* Input          : nus: Number of us want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/		    								   
void delay_us(u32 nus)
{		
    TIM_Cmd(TIM1, ENABLE);
    TIM1->CNT = nus;
    while((TIM1->CNT > 0) && (TIM1->CNT <= nus)); 
    TIM_Cmd(TIM1, DISABLE);
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : delay nms
*                  
* Input          : nms: Number of ms want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void delay_ms(u16 nms)
{	 		  	  
    u16 i=0;
    
    for( i = 0; i < nms; i++ )
    {
        delay_us(1000);
    }  
} 

#else

/*******************************************************************************
* Function Name  : Delay_Init
* Description    : Coarse delay function
*                  Initialization delay function
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_Init(void)	 
{
 
}


/*******************************************************************************
* Function Name  : delay_us
* Description    : Microsecond delay
*                  
* Input          : nus: Number of us want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void delay_us(u32 nus)
{    
   u16 i=0;  
   while(nus--)
   {
      i=6;  
      while(i--) ;    
   }
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : Millisecond delay
*                  
* Input          : nms: Number of ms want to delay
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void delay_ms(u16 nms)
{    
   u16 i=0;  
   while(nms--)
   {
      i=8000;  
      while(i--) ;    
   }
}
#endif




/******************************  END OF FILE  *********************************/

