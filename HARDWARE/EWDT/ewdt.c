
#include "sys.h"
#include "delay.h"
#include "ewdt.h"

//min:1.12 typ:1.6 max:2.4

void EWDT_Drv_pin_config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR | RCC_APB2Periph_GPIOC, ENABLE );
  
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA , &GPIO_InitStruct);

}

/*******************************************************************************
*******************************************************************************/
void write_bkp(u16 adr,u16 dat)
{
  PWR_BackupAccessCmd(ENABLE);
  BKP_WriteBackupRegister(adr, dat);   
  PWR_BackupAccessCmd(DISABLE);
}

/*******************************************************************************
*******************************************************************************/
u8 ext_WDT_check(void)
{
  u16 bkr_rst_flag=0;

  delay_ms(10); 
  EWDT_TOOGLE();
  delay_ms(10);    
  EWDT_TOOGLE();
  delay_ms(10);    
  EWDT_TOOGLE();
    
  bkr_rst_flag = BKP_ReadBackupRegister(BKP_DR1);
  if(bkr_rst_flag == 0xfa01)
  {
    if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != SET)
    {
      write_bkp(BKP_DR1, 0);  
      RCC_ClearFlag();   
//      EN_ERROR_SYS1 |= 0x01;
    }   
  }  
  else
  {

    write_bkp(BKP_DR1, 0xfa01);   
    RCC_ClearFlag();
    
    delay_ms(2000);    
    
//    EN_ERROR_SYS1 |= 0x01;
  }  
  
  write_bkp(BKP_DR1, 0);  
  
  return(0);
}  

/*******************************************************************************
*******************************************************************************/
void power_on_bsp_check(void)
{
  //Õ‚÷√ø¥√≈π∑ºÏ≤‚£¨π ’œF81
  ext_WDT_check();
}


/*******************************************************************************
*******************************************************************************/