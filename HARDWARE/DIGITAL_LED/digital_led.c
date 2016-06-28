/*******************************************************************************
* File Name          : digital_led.c
* Author             : lison
* Version            : V1.0
* Date               : 03/23/2016
* Description        : This file contains digital led driver functions.
*                      
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "digital_led.h"
#include "sys.h"
#include "delay.h"
#include "ewdt.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define LED_NUM1        PAout(4)
#define LED_NUM2        PAout(5)
#define LED_NUM3        PAout(6)
#define LED_SCLK        PBout(1)
#define LED_RCLK        PBout(0)
#define LED_OE          PCout(5)
#define LED_SDI         PCout(4) 

/* Private variables ---------------------------------------------------------*/
const u8 bcd[11] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff}; //0~9£¬null

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

u8 dis_data[3]={0,0,0};

/*******************************************************************************
* Function Name  : digital_led_gpio_init
* Description    : Initialize digital led gpio.
*                  
* Input          : None
*                  
* Output         : None
* Return         : None
*******************************************************************************/
void digital_led_gpio_init(void)
{
    
#ifdef GEC_DBL1
      GPIO_InitTypeDef GPIO_InitStructure;
          
      /* Enable GPIO clock */
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);
      
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);    
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
      GPIO_Init(GPIOC, &GPIO_InitStructure);      
      
#else
      
      GPIO_InitTypeDef GPIO_InitStruct;
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;             
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;       
      GPIO_Init(GPIOA, &GPIO_InitStruct);    
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
      GPIO_Init(GPIOB, &GPIO_InitStruct);  
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; 
      GPIO_Init(GPIOC, &GPIO_InitStruct);        
#endif     
      LED_OE = 0;
      delay_ms(2);
      LED_OE = 1;
}

/*******************************************************************************
* Function Name  : txbyte
* Description    : Data Conversion
*                  
* Input          : dat: Need to convert digital
*                  
* Output         : None
* Return         : None
*******************************************************************************/
void txbyte(u8 dat)
{
    u8 i,j,k;
    
    LED_OE = 0;
    j = dat;
    for(i = 0; i < 8; i++)
    {
        LED_SCLK = 0;
      
        k = (j&0x80)>>7;
        
        LED_SDI = k;
                                  
        j <<= 1;
        
        LED_SCLK = 1;
    }
    
    LED_RCLK = 0;
    delay_us(1);
    LED_RCLK = 1;
}

/*******************************************************************************
* Function Name  : led_display
* Description    : Digital led display.
*                  
* Input          : None
*                  
* Output         : None
* Return         : None
*******************************************************************************/
void led_display(void)
{
  static u32 dis_cnt=0;
  
  dis_cnt++;
  if(dis_cnt>2) dis_cnt=0;
  
  LED_NUM1 = 1;
  LED_NUM2 = 1;
  LED_NUM3 = 1;

  txbyte(bcd[dis_data[dis_cnt]]);
  
  if(dis_cnt==0) 
  {
    LED_NUM1 = 0; 
  } 
  else if(dis_cnt==1) 
  {
    LED_NUM2 = 0; 
  }  
  else if(dis_cnt==2) 
  {
    LED_NUM3 = 0; 
  }    
}

/*******************************************************************************
* Function Name  : digital_led_check
* Description    : Check the digital led.
*                  
* Input          : None
*                  
* Output         : None
* Return         : None
*******************************************************************************/
void digital_led_check(void)
{
    u8 count = 0;
  
    for(u8 i = 0; i < 11; i++)
    {
        count = 100;
        
        for(u8 j = 0; j < 3; j++)
        {
          dis_data[j] = i;
        }
        
        while(count)
        {
          led_display();
          delay_ms(2);              
          count--;
        }  
        
        EWDT_TOOGLE();
    }
}

/******************************  END OF FILE  *********************************/



