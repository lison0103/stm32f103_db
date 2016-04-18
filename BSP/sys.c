/*******************************************************************************
* File Name          : sys.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
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
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
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
* Description    : 
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


/*******************************************************************************
* Function Name  : GetLockCode
* Description    : 
*                  
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
u32 GetLockCode(void)
{
  
   u32 CpuID[3];
   u32 Lock_Code;  
  
  /** acquire the cpu unique ID **/
  CpuID[0]=*(vu32*)(0x1ffff7e8);
  CpuID[1]=*(vu32*)(0x1ffff7ec);
  CpuID[2]=*(vu32*)(0x1ffff7f0);
  
//  printf("\r\nSerial Number:%08X%08X%08X\r\n",CpuID[0],CpuID[1],CpuID[2]);
  
  /** encryption **/
  Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
   
  return Lock_Code;
}


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM("WFI");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{
	__ASM("CPSID I");    		  
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM("CPSIE I");		  
}
//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(u32 addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

/******************************  END OF FILE  *********************************/



