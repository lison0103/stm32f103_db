#include "sys.h"
#include "delay.h"
#include "hw_test.h"
#include "led.h"
#include "digital_led.h"

extern u8 dis_data[3];

void HW_TEST_INIT(void)
{
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE );
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
  
      GPIO_InitTypeDef GPIO_InitStruct;

      //input
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;             
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;       
      GPIO_Init(GPIOA , &GPIO_InitStruct);    
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOB , &GPIO_InitStruct);        

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;                  
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                  
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;                  
      GPIO_Init(GPIOE , &GPIO_InitStruct);        
      
      //output
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
            
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
      GPIO_Init(GPIOB , &GPIO_InitStruct);  
      
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
      GPIO_Init(GPIOE , &GPIO_InitStruct);  

}

void HW_TEST(void)
{
    u8 sflag,t,inputnum = 0;
  
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
    
    while(1)
    {
        sflag = 0;
        
        if ( IN1 )
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0;
            OTP1 = 0;
                        
            inputnum = 1;
            sflag++;
        }
        if ( IN2 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0;         
            OTP1 = 0;
            
            inputnum = 2;
            sflag++;
        }
        if ( IN3 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0;          
            OTP1 = 0;
                        
            inputnum = 3;
            sflag++;

        }
        if ( IN4 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 0;         
            OTP1 = 0;
            
            inputnum = 4;
            sflag++;
        } 
        if ( IN5 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 0;     
            OTP1 = 0;
                        
            inputnum = 5;
            sflag++;
        }
        if ( IN6 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 0;        
            OTP1 = 0;
                        
            inputnum = 6;
            sflag++;

        }
        if ( IN7 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 0;         
            OTP1 = 0;
                        
            inputnum = 7;
            sflag++;

        }        
        if ( IN8 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 0;        
            OTP1 = 0;
                        
            inputnum = 8;
            sflag++;

        }
        if ( IN9 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 0;  
            OTP1 = 0;
                        
            inputnum = 9;
            sflag++;

        }
        if ( IN10 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 0;     
            OTP1 = 0;
                        
            inputnum = 10;
            sflag++;

        } 
        if ( IN11 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 0;     
            OTP1 = 0;
                        
            inputnum = 11;
            sflag++;

        }
        if ( IN12 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 0;       
            OTP1 = 0;
                        
            inputnum = 12;
            sflag++;

        }
        if ( IN13 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 0;      
            OTP1 = 0;
                        
            inputnum = 13;
            sflag++;

        }         
        if ( IN14 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 0;      
            OTP1 = 0;
                        
            inputnum = 14;
            sflag++;

        }
        if ( IN15 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 0;       
            OTP1 = 0;
                        
            inputnum = 15;
            sflag++;

        }
        if ( IN16 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 1;     
            OTP1 = 0;
                        
            inputnum = 16;
            sflag++;

        }    
        if ( IN17 )
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 1;
            OTP1 = 0;
                        
            inputnum = 17;
            sflag++;
        }
        if ( IN18 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 1;         
            OTP1 = 0;
            
            inputnum = 18;
            sflag++;
        }
        if ( IN19 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 1;          
            OTP1 = 0;
                        
            inputnum = 19;
            sflag++;

        }
        if ( IN20 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 1;         
            OTP1 = 0;
            
            inputnum = 20;
            sflag++;
        } 
        if ( IN21 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 1;     
            OTP1 = 0;
                        
            inputnum = 21;
            sflag++;
        }
        if ( IN22 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 1;        
            OTP1 = 0;
                        
            inputnum = 22;
            sflag++;

        }
        if ( IN23 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 0;
            OCP5 = 1;         
            OTP1 = 0;
                        
            inputnum = 23;
            sflag++;

        }        
        if ( IN24 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 1;        
            OTP1 = 0;
                        
            inputnum = 24;
            sflag++;

        }
        if ( IN25 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 1;  
            OTP1 = 0;
                        
            inputnum = 25;
            sflag++;

        }
        if ( IN26 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 1;     
            OTP1 = 0;
                        
            inputnum = 26;
            sflag++;

        } 
        if ( IN27 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 0;
            OCP4 = 1;
            OCP5 = 1;     
            OTP1 = 0;
                        
            inputnum = 27;
            sflag++;

        }
        if ( IN28 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 1;       
            OTP1 = 0;
                        
            inputnum = 28;
            sflag++;

        }
        if ( IN29 ) 
        {
            OCP1 = 1;
            OCP2 = 0;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 1;      
            OTP1 = 0;
                        
            inputnum = 29;
            sflag++;

        }         
        if ( IN30 ) 
        {
            OCP1 = 0;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 1;      
            OTP1 = 0;
                        
            inputnum = 30;
            sflag++;

        }
        if ( IN31 ) 
        {
            OCP1 = 1;
            OCP2 = 1;
            OCP3 = 1;
            OCP4 = 1;
            OCP5 = 1;       
            OTP1 = 0;
            
            inputnum = 31;
            sflag++;

        }
        if ( IN32 ) 
        {
            OCP1 = 0;
            OCP2 = 0;
            OCP3 = 0;
            OCP4 = 0;
            OCP5 = 0; 
            OTP1 = 1;
            
            inputnum = 32;
            sflag++;

        }

        
        if(sflag > 1)
        {
            OTP2 = 1; 
            dis_data[0] = 0;
            dis_data[1] = 0;
            dis_data[2] = 0;
        }
        else
        {
            OTP1 = 0; 
            dis_data[0] = 0;
            dis_data[1] = inputnum/10;
            dis_data[2] = inputnum%10;
        }
        
        led_display();
        
        delay_ms(1);
        t++;
        if(t==200)
        {
            LED=!LED;
            t=0;
        }        
        
    }
}