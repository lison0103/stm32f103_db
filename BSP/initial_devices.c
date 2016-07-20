/*******************************************************************************
* File Name          : initial_devices.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains the devices initinal.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "initial_devices.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void PVD_Configuration(void);



/*******************************************************************************
* Function Name  : Initial_Device
* Description    : Initialize the CPU and peripherals.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Initial_Device(void)
{
 
        /** set system interrupt priority group 2 **/
	NVIC_Configuration();
        
        /** RCC  and  PVD Configuration **/
        RCC_Configuration();   
        PVD_Configuration();
        
        /** delay init **/
	Delay_Init();  

        /** LED init **/
	LED_Init();
        
        /** input and relay output test init **/
        Input_Output_PinInit();        
        
        /** ewdt init **/
        EWDT_Drv_pin_config();
        ExtWdtCheck();
        
        /** digital led init **/
        digital_led_gpio_init();               
        digital_led_check();
             
        /** CAN1 init,baud rate 500Kbps **/
	CAN_Int_Init(CAN1);   
        
        /* systick timer , 5ms interrupt */
 	if(SysTick_Config(SystemCoreClock / 200))
        {
          /* Capture error */
          while (1);
        }
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2); 

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
#ifdef GEC_DBL1
    FLASH_PrefetchBufferCmd(ENABLE);
#else
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
#endif
    
    /* PLLCLK = 8MHz * 9 = 72 MHz */
#ifdef GEC_DBL1
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#endif
    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }

    
    /* Enable GPIO and Peripherals clocks */   
#ifdef GEC_DBL1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1 , ENABLE);    
                                          
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA
                           |RCC_AHBPeriph_GPIOB
                           |RCC_AHBPeriph_GPIOC
                           |RCC_AHBPeriph_GPIOD
                           |RCC_AHBPeriph_GPIOE ,
                           ENABLE);
#else    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE );
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1 , ENABLE);    
                                        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA
                           |RCC_APB2Periph_GPIOB
                           |RCC_APB2Periph_GPIOC
                           |RCC_APB2Periph_GPIOD
                           |RCC_APB2Periph_GPIOE ,
                           ENABLE); 
#endif  

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE); 
  
      
    /* Enable CSS */
    RCC_ClockSecuritySystemCmd(ENABLE);
}


/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configuring NVIC interrupt group.
*                  
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
    
//    INTX_ENABLE();

}

/*******************************************************************************
* Function Name  : PVD_Configuration
* Description    : Configuring system Voltage Detector.
*                  
* Input          : None
*                 
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_Configuration(void)
{
  
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    EXTI_InitStructure.EXTI_Line = EXTI_Line16;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Falling;//EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable the PVD Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

#ifdef GEC_DBL1
    PWR_PVDLevelConfig(PWR_PVDLevel_4);  
#else
    PWR_PVDLevelConfig(PWR_PVDLevel_2V5);
#endif
    PWR_PVDCmd(ENABLE);

}


/******************************  END OF FILE  *********************************/


