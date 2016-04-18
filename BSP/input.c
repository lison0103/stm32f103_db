/*******************************************************************************
* File Name          : input.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : 
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
* Description    : 
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Input_Check(void)
{
         
        dis_data[0] = 0;
        dis_data[1] = 0;
        dis_data[2] = 0;
    

        sflag = 0;
        inputnum = 0;
        
        if ( IN1 )
        {         
            inputnum = 1;
            sflag++;
        }
        if ( IN2 ) 
        {
            inputnum = 2;
            sflag++;
        }
        if ( IN3 ) 
        {          
            inputnum = 3;
            sflag++;

        }
        if ( IN4 ) 
        {
            inputnum = 4;
            sflag++;
        } 
        if ( IN5 ) 
        {          
            inputnum = 5;
            sflag++;
        }
        if ( IN6 ) 
        {        
            inputnum = 6;
            sflag++;

        }
        if ( IN7 ) 
        {         
            inputnum = 7;
            sflag++;

        }        
        if ( IN8 ) 
        {         
            inputnum = 8;
            sflag++;

        }
        if ( IN9 ) 
        {          
            inputnum = 9;
            sflag++;

        }
        if ( IN10 ) 
        {                
            inputnum = 10;
            sflag++;

        } 
        if ( IN11 ) 
        {       
            inputnum = 11;
            sflag++;

        }
        if ( IN12 ) 
        {          
            inputnum = 12;
            sflag++;

        }
        if ( IN13 ) 
        {           
            inputnum = 13;
            sflag++;

        }         
        if ( IN14 ) 
        {          
            inputnum = 14;
            sflag++;

        }
        if ( IN15 ) 
        {          
            inputnum = 15;
            sflag++;

        }
        if ( IN16 ) 
        {            
            inputnum = 16;
            sflag++;

        }    
        if ( IN17 )
        {         
            inputnum = 17;
            sflag++;
        }
        if ( IN18 ) 
        {
            inputnum = 18;
            sflag++;
        }
        if ( IN19 ) 
        {          
            inputnum = 19;
            sflag++;

        }
        if ( IN20 ) 
        {
            inputnum = 20;
            sflag++;
        } 
        if ( IN21 ) 
        {              
            inputnum = 21;
            sflag++;
        }
        if ( IN22 ) 
        {             
            inputnum = 22;
            sflag++;

        }
        if ( IN23 ) 
        {               
            inputnum = 23;
            sflag++;

        }        
        if ( IN24 ) 
        {              
            inputnum = 24;
            sflag++;

        }
        if ( IN25 ) 
        {              
            inputnum = 25;
            sflag++;

        }
        if ( IN26 ) 
        {                 
            inputnum = 26;
            sflag++;

        } 
        if ( IN27 ) 
        {                
            inputnum = 27;
            sflag++;

        }
        if ( IN28 ) 
        {
            inputnum = 28;
            sflag++;

        }
        if ( IN29 ) 
        {               
            inputnum = 29;
            sflag++;

        }         
        if ( IN30 ) 
        {                
            inputnum = 30;
            sflag++;

        }
        if ( IN31 ) 
        {         
            inputnum = 31;
            sflag++;

        }
        if ( IN32 ) 
        {      
            inputnum = 32;
            sflag++;

        }

        if(inputnum == 0)
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0;
            
            OTP1 = 0;
            OTP2 = 0;
            OTP3 = 0; 
            
            
            dis_data[0] = 0;
            dis_data[1] = 0;
            dis_data[2] = 0;
        }        
        else if(sflag > 1)
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0;
            
            OTP1 = 0;
            OTP2 = 0;
            OTP3 = 0; 
            
            
            dis_data[0] = 0;
            dis_data[1] = 0;
            dis_data[2] = 0;
        }
        else
        {
            switch(inputnum)
            {
                case 1:
                  OCP1 = 1;break;
                case 2:
                  OCP2 = 1;break;
                case 3:
                  OCP3 = 1;break;
                case 4:
                  OCP4 = 1;break;
                case 5:
                  OCP5 = 1;break;
                case 6:
                  OTP1 = 1;break; 
                case 7:
                  OTP2 = 1;break;
                case 8:
                  OTP3 = 1;break;
                case 9:
                  OCP1 = 1;break;
                case 10:
                  OCP2 = 1;break;
                case 11:
                  OCP3 = 1;
                  break;
                case 12:
                  OCP4 = 1;   
                  break;
                case 13:
                  OCP5 = 1;
                  break;
                case 14:
                  OTP1 = 1;
                  break;
                case 15:
                  OTP2 = 1;
                  break;
                case 16:
                  OTP3 = 1; 
                  break;
                case 17:
                  OCP1 = 1;break;
                case 18:
                  OCP2 = 1;break;
                case 19:
                  OCP3 = 1;break;
                case 20:
                  OCP4 = 1;break;
                case 21:
                  OCP5 = 1;break;
                case 22:
                  OTP1 = 1;break; 
                case 23:
                  OTP2 = 1;break;
                case 24:
                  OTP3 = 1;break;
                case 25:
                  OCP1 = 1;break;
                case 26:
                  OCP2 = 1;break;
                case 27:
                  OCP3 = 1;
                  break;
                case 28:
                  OCP4 = 1;   
                  break;
                case 29:
                  OCP5 = 1;
                  break;
                case 30:
                  OTP1 = 1;
                  break;
                case 31:
                  OTP2 = 1;
                  break;
                case 32:
                  OTP3 = 1; 
                  break;                  
                  
                default:
                  break;
            }
            
            dis_data[0] = 0;
            dis_data[1] = inputnum/10;
            dis_data[2] = inputnum%10;
        }
        
        led_display();
 
}

/*******************************************************************************
* Function Name  : Can_comm
* Description    : 
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




