/*******************************************************************************
* File Name          : hw_test.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains the DBL1 hardware test function.
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_test.h"
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 sflag,inputnum = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


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
* Function Name  : HardwareTEST
* Description    : Test the board.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void HardwareTEST(void)
{
    u8 testdata[10];
    u8 testerror = 0;
    u8 len = 0;
    u16 waittms = 0;
    
    if( ReadSwDp() == 0x00 )
    {
        kz_data_array[0] = 0xfa;
    }
    
    CAN1_TX_Data[0] = 0xf1;
    testdata[0] = 0xf1;
    for( u8 i = 1; i < 10 ; i++ )
    {
        CAN1_TX_Data[i] = i + 0xa0;
        testdata[i] = i + 0xa0;
    }
    BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1_TEST_ID, CAN1_TX_Data, 10);
    
    do
    {
        len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);
        delay_ms(1);
        EWDT_TOOGLE();
        waittms++;
        if( waittms > 5000 )
        {
            waittms = 0;
            break;
        }
    }
    while( len != 10 || CAN1_RX_Data[0] != 0xf1 );     
    
    if( len == 10 && CAN1_RX_Data[0] == 0xf1 )
    {
        waittms = 0;
        for( u8 i = 2; i < 10 ; i++ )
        {
            CAN1_TX_Data[i] = CAN1_RX_Data[i];
        }
        BSP_CAN_Send(CAN1, &CAN1_TX_UpDown, CAN1_TEST_ID, CAN1_TX_Data, 10);
        
        do
        {
            len = BSP_CAN_Receive(CAN1, &CAN1_RX_UpDown, CAN1_RX_Data, 0);
            delay_ms(1);
            EWDT_TOOGLE();
            waittms++;
            if( waittms > 5000 )
            {
                waittms = 0;
                break;
            }
        }
        while( len != 10 || CAN1_RX_Data[0] != 0xf1 ); 
        
        if( len == 10 && CAN1_RX_Data[0] == 0xf1 )
        {
            for( u8 i = 2; i < 10 ; i++ )
            {
                if( CAN1_RX_Data[i] != testdata[i] )
                {
                    testerror = 1;
                    break;
                }
            }
            
            if( testerror == 0 )
            {
                if( CAN1_RX_Data[1] == 0xb1 )
                {
                    testmode = 1;
                }               
            }
        } 
        
        
    }
    else
    {
        CAN_FilterInitTypeDef  	        CAN_FilterInitStructure;
        /* CAN1 filter init */
        CAN_FilterInitStructure.CAN_FilterNumber=0;	
        CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	
        CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	
        
        CAN_FilterInitStructure.CAN_FilterIdHigh = (((u32)CAN1RX_UP_ID << 3) & 0xFFFF0000 ) >> 16;	
        CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)CAN1RX_UP_ID << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;
        CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) & 0xFFFF0000) >> 16;
        CAN_FilterInitStructure.CAN_FilterMaskIdLow = ((((u32)(~( CAN1RX_UP_ID ^ CAN1RX_DOWN_ID ))) << 3) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF;  
        
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
        CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
        CAN_FilterInit(&CAN_FilterInitStructure);          
    }
}


/******************************  END OF FILE  *********************************/



