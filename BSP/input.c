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
        u8 Dip_value;
        u8 i;

        if( testmode == 1 )        
        {
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
            
            Dip_value = ReadSwDp();
            for( i = 0; i < 4; i++ )
            {
                if( Dip_value & ((u8)( 1 << i )))
                {
                    sflag++;
                    inputnum = i + 33;
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
                
                //            *ulPt_Output |= ( 1 << ( ( inputnum - 1 ) % 8 ));
                if( inputnum <= 32 )
                {
                    *ulPt_Output |= ( inputnum );
                }
                else
                {
                    switch( Dip_value )
                    {
                       case 0x01: *ulPt_Output |= ( inputnum );break; 
                       case 0x02: *ulPt_Output |= ( inputnum + 32 );break; 
                       case 0x04: *ulPt_Output |= ( inputnum + 97 );break;
                       case 0x08: *ulPt_Output |= ( inputnum + 164 );break;
                       default: *ulPt_Output = 0;; 
                    }
                }
                dis_data[0] = 0;
                dis_data[1] = inputnum/10;
                dis_data[2] = inputnum%10;
            }
        }    
 
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
     
    static u8 can1_comm_timeout = 0;
    u8 len = 0;
    
    if( can1_receive == 1 )
    {
        can1_receive = 0;
        can1_comm_timeout = 0;
    }
    else if( ++can1_comm_timeout >= 3 )
    {
        /*  can communication timeout process */
    }     
    
    len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);
    
    for( u8 i = 4; i < 8; i++ )
    {
        CAN1_TX_Data[i] = EscRTBuff[i];
    }
    
    if( len > 0 )
    {
        CAN1_TX_Data[0] = CAN1_RX_Data[0];
        CAN1_TX_Data[1] = CAN1_RX_Data[1];
    }

        
    /* DBL1 UP */
    if( kz_data_array[0] == 0x55 )
    {
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_UP_ID, CAN1_TX_Data, 20);           
    }
    /* DBL1 DOWN */
    else if( kz_data_array[0] == 0xaa )
    {
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_DOWN_ID, CAN1_TX_Data, 20);
    }
    /* Test Mode */
    else if( testmode == 1 )
    {               
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1TX_DOWN_ID, CAN1_TX_Data, 20);
    }		   

}

/******************************  END OF FILE  *********************************/




