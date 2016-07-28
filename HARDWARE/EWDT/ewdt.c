/*******************************************************************************
* File Name          : ewdt.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : This file contains the external watchdog functions.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "delay.h"
#include "ewdt.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

u8 iwdg_check_flag = 0;

/*******************************************************************************
* Function Name  : EWDT_Drv_pin_config
* Description    : Configure the pin.
*                  the external watchdog reset  min:1.12 typ:1.6 max:2.4
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void EWDT_Drv_pin_config(void)
{

#ifdef GEC_DBL1
    GPIO_InitTypeDef GPIO_InitStructure;
        
    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

#else    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR | RCC_APB2Periph_GPIOA, ENABLE );
  
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
#endif
}

/*******************************************************************************
* Function Name  : write_bkp
* Description    : This function write the cpu backup register to store data.
*                  
* Input          : adr: the address of backup register
*                  dat: data to be written
* Output         : None
* Return         : None
*******************************************************************************/
void write_bkp(u16 adr,u16 dat)
{
  PWR_BackupAccessCmd(ENABLE);
#ifdef GEC_DBL1
  RTC_WriteBackupRegister(adr, dat);    
#else
  BKP_WriteBackupRegister(adr, dat);
#endif
  PWR_BackupAccessCmd(DISABLE);
}

/*******************************************************************************
* Function Name  : ExtWdtCheck
* Description    : Check the external watchdog.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void ExtWdtCheck(void)
{
  u16 bkr_rst_flag=0;

  delay_ms(10); 
  EWDT_TOOGLE();
  delay_ms(10);    
  EWDT_TOOGLE();
  delay_ms(10);    
  EWDT_TOOGLE();
    
#ifdef GEC_DBL1
  bkr_rst_flag = RTC_ReadBackupRegister(RTC_BKP_DR1);
#else
  bkr_rst_flag = BKP_ReadBackupRegister(BKP_DR1);
#endif
  if(bkr_rst_flag == 0xfa01)
  {
    if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != SET)
    {
#ifdef GEC_DBL1
      write_bkp(RTC_BKP_DR1, 0);  
#else
      write_bkp(BKP_DR1, 0);
#endif
      RCC_ClearFlag();   
//      EN_ERROR_SYS1 |= 0x01;
    }   
  }  
  else
  {
#ifdef GEC_DBL1
    write_bkp(RTC_BKP_DR1, 0xfa01);    
#else
    write_bkp(BKP_DR1, 0xfa01);   
#endif
    RCC_ClearFlag();
    
    delay_ms(2000);    
    
//    EN_ERROR_SYS1 |= 0x01;
  }  
#ifdef GEC_DBL1
  write_bkp(RTC_BKP_DR1, 0); 
#else  
  write_bkp(BKP_DR1, 0);  
#endif

}  



/******************************  END OF FILE  *********************************/


