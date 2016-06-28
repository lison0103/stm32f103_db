/*******************************************************************************
* File Name          : main.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Main program body.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "initial_devices.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static u16 Tms10Counter = 0,Tms20Counter = 0,Tms50Counter = 0,Tms100Counter = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

u32 TimingDelay = 0;
u32 SysRunTime = 0; 
u8 kz_data_array[30];
u8 EscRTBuff[100]; 

/*******************************************************************************
* Function Name  : LED_indicator
* Description    : LED indicator flashes Timing.                  
* Input          : None                 
* Output         : None
* Return         : None
*******************************************************************************/
void LED_indicator(void)
{
	static u32 led_idr_cnt = 0;	 
	
	led_idr_cnt++;
	
	if( led_idr_cnt >= 100 )
	{
                led_idr_cnt = 0;
		LED=!LED;                
	}   
}


/*******************************************************************************
* Function Name  : Task_Loop
* Description    : This function contains the task to be executed in a loop.
* Input          : None                
* Output         : None
* Return         : None
*******************************************************************************/
void Task_Loop(void)
{          

      if( ++Tms10Counter >= 2 ) Tms10Counter = 0;
      if( ++Tms20Counter >= 4 ) Tms20Counter = 0;
      if( ++Tms50Counter >= 9 ) Tms50Counter = 0;
      if( ++Tms100Counter >= 19 ) Tms100Counter = 0;     

      
      Get_GpioInput(&EscRTBuff[4]);
      output_driver(&EscRTBuff[30]);
      
      if( Tms10Counter == 0 )
      {
        
      }      
      if( Tms20Counter == 0 )
      {
          GetAdr();
      }  
         
      if( Tms50Counter == 0 )
      {                                 
          /* Reload EWDT counter */          
          EWDT_TOOGLE();
          
          Input_Check();           
          CAN_Comm();  
      } 
      
      if( Tms100Counter == 0 )
      {         

      }
           
     
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program.                 
* Input          : None                 
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{        
  
    /** hardware init **/
    Initial_Device();    
    
    while(1)
    {
      
        /* 5ms */
        while ( !TimingDelay );
        TimingDelay = 0;

        Task_Loop();
        LED_indicator();
   
    }          
          
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/******************************  END OF FILE  *********************************/



