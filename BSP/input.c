/*******************************************************************************
* File Name          : input.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains input test function.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "delay.h"
#include "input.h"
#include "led.h"
#include "digital_led.h"
#include "can.h"
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern u8 dis_data[3];
u8 sflag,inputnum = 0;

/*******************************************************************************
* Function Name  : Input_Check
* Description    : Monitor the input pin status and test.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Input_Check(void)
{
        u32 *ulPt_Input;
        u8 *ulPt_Output;
        u8 i;
        
        ulPt_Input = (u32*)&EscRTBuff[4];
        ulPt_Output = &EscRTBuff[30];
        
        dis_data[0] = 0;
        dis_data[1] = 0;
        dis_data[2] = 0;
    
        sflag = 0;
        inputnum = 0;      
        
        
        for( i = 0; i < 32; i++ )
        {
            if( *ulPt_Input & ((u32)( 1 << i )))
            {
                sflag++;
                inputnum = i + 1;
            }
        }        

        if(( inputnum == 0 ) || ( sflag > 1 ))
        {

            *ulPt_Output = 0;
   
            dis_data[0] = 0;
            dis_data[1] = 0;
            dis_data[2] = 0;
        }        
        else
        {                        
  
            *ulPt_Output |= ( 1 << ( ( inputnum - 1 ) % 8 ));
     
            dis_data[0] = 0;
            dis_data[1] = inputnum/10;
            dis_data[2] = inputnum%10;
        }
        
        led_display();
 
}

/*******************************************************************************
* Function Name  : Can_comm
* Description    : Can communication.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_Comm(void)
 {	 
	u8 i=0;
	u8 canbuf[8];
         
        
        for(i=0;i<8;i++)
        {
            canbuf[i]=i;            
        }
        
        /* DBL1 UP */
        if( kz_data_array[0] == 1 )
        {
            Can_Send_Msg( CAN1, 0x3456, canbuf, 8 );
        }
        /* DBL1 DOWN */
        else if( kz_data_array[0] == 2 )
        {
            Can_Send_Msg( CAN1, 0x3488, canbuf, 8 );
        }
		   

}

/******************************  END OF FILE  *********************************/




