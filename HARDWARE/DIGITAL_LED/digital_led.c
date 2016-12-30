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
#include "delay.h"
#include "ewdt.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define LED_NUM1_SET()        GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define LED_NUM1_CLR()        GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define LED_NUM2_SET()        GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define LED_NUM2_CLR()        GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define LED_NUM3_SET()        GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define LED_NUM3_CLR()        GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define LED_SCLK_SET()        GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define LED_SCLK_CLR()        GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define LED_RCLK_SET()        GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define LED_RCLK_CLR()        GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LED_OE_SET()        GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define LED_OE_CLR()        GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define LED_SDI_SET()        GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define LED_SDI_CLR()        GPIO_ResetBits(GPIOC,GPIO_Pin_4)


/* Private variables ---------------------------------------------------------*/
const u8 bcd[13] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x8e,0x88,0xff}; //0~9, F, A null

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void led_display1(void);

u8 dis_data[3]={0,0,0};
u8 g_u8LedFlash = 0u;

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
          
      LED_OE_CLR();
      delay_ms(2);
      LED_OE_SET();
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
    u8 i,j;
    
    LED_OE_CLR();
    j = dat;
    for(i = 0; i < 8; i++)
    {
        LED_SCLK_CLR();
      
        if((j & 0x80) >> 7)
        {
            LED_SDI_SET();
        }
        else
        {
            LED_SDI_CLR();
        }
                                  
        j <<= 1;
        
        LED_SCLK_SET();
    }
    
    LED_RCLK_CLR();
    delay_us(1);
    LED_RCLK_SET();
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
static void led_display1(void)
{
  static u32 dis_cnt=0;
  
  dis_cnt++;
  if(dis_cnt>2) dis_cnt=0;
  
  LED_NUM1_SET();
  LED_NUM2_SET();
  LED_NUM3_SET();

  txbyte(bcd[dis_data[dis_cnt]]);
  
  if(dis_cnt==0) 
  {
    LED_NUM1_CLR(); 
  } 
  else if(dis_cnt==1) 
  {
    LED_NUM2_CLR(); 
  }  
  else if(dis_cnt==2) 
  {
    LED_NUM3_CLR(); 
  }    
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
    static u16 stat_u16TimerLedFlash =0;
  
    if( g_u8LedFlash == 1u )
    {
        stat_u16TimerLedFlash++;
        if( stat_u16TimerLedFlash >= 200u )
        {
            stat_u16TimerLedFlash = 0u;
            LED_NUM1_SET();
            LED_NUM2_SET();
            LED_NUM3_SET();
        }
        else if( stat_u16TimerLedFlash >= 100u )
        {
            led_display1();
        }
        else
        {}
    }
    else
    {
        led_display1();
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



