/*******************************************************************************
* File Name          : delay.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define  USE_SYSTICK_DELAY   0

/* Private variables ---------------------------------------------------------*/
#if USE_SYSTICK_DELAY
static u8  fac_us=0;
static u16 fac_ms=0;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/	 
	 


#if USE_SYSTICK_DELAY

/*******************************************************************************
* Function Name  : delay_init
* Description    : 
*                  
* Input          : 
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void delay_init(void)	 
{
  
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us=SystemCoreClock/8000000;	 
	 
	fac_ms=(u16)fac_us*1000;   
}	

/*******************************************************************************
* Function Name  : delay_us
* Description    : 
*                  
* Input          : 
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
* Description    : 
*                  
* Input          : 
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


#else


void delay_init()	 
{
 
}

//粗延时函数，微秒
void delay_us(u32 nus)
{    
   u16 i=0;  
   while(nus--)
   {
      i=6;  //自己定义
      while(i--) ;    
   }
}
//毫秒级的延时
void delay_ms(u16 nms)
{    
   u16 i=0;  
   while(nms--)
   {
      i=8000;  //自己定义
      while(i--) ;    
   }
}
#endif




/******************************  END OF FILE  *********************************/
























