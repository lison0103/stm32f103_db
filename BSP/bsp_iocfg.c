/*******************************************************************************
* File Name          : bsp_iocfg.c
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains input and output pin Initializes.
*                      
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_iocfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Get_GpioInput
* Description    : Get GPIO input pin value.
*                  
* Input          : inBuff: read the gpio pin value of data
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Get_GpioInput(u8 inBuff[])
{     

    static u16 PinValue[3][5],ByteAnd[5],ByteOr[5],read_pin_cnt = 0;
    u16 i; 
    
    /* first, clear the data */
    for(i = 0; i < 4; i++)
    {
        inBuff[i] = 0;
    }
    
    read_pin_cnt++;  
    if(read_pin_cnt > 2) read_pin_cnt = 0;  
    
    /* Read I/O port */                      
    PinValue[read_pin_cnt][0] = GPIO_ReadInputData(GPIOA);
    PinValue[read_pin_cnt][1] = GPIO_ReadInputData(GPIOB);
    PinValue[read_pin_cnt][2] = GPIO_ReadInputData(GPIOC);
    PinValue[read_pin_cnt][3] = GPIO_ReadInputData(GPIOD);
    PinValue[read_pin_cnt][4] = GPIO_ReadInputData(GPIOE);
    
    for( i = 0; i < 5; i++ )
    {   
        ByteAnd[i] = PinValue[0][i] & PinValue[1][i] & PinValue[2][i];
        ByteOr[i] = PinValue[0][i] | PinValue[1][i] | PinValue[2][i]; 
    }
    

    
    /* IN1 ~ IN8 */
    if(ByteAnd[4] & ( 1 << 10 )) inBuff[0] |= 0x01; else if(!(ByteOr[4] & ( 1 << 10 ))) inBuff[0] &= ~0x01; 
    if(ByteAnd[4] & ( 1 << 11 )) inBuff[0] |= 0x02; else if(!(ByteOr[4] & ( 1 << 11 ))) inBuff[0] &= ~0x02; 
    if(ByteAnd[4] & ( 1 << 12 )) inBuff[0] |= 0x04; else if(!(ByteOr[4] & ( 1 << 12 ))) inBuff[0] &= ~0x04; 
    if(ByteAnd[4] & ( 1 << 13 )) inBuff[0] |= 0x08; else if(!(ByteOr[4] & ( 1 << 13 ))) inBuff[0] &= ~0x08; 
    if(ByteAnd[4] & ( 1 << 14 )) inBuff[0] |= 0x10; else if(!(ByteOr[4] & ( 1 << 14 ))) inBuff[0] &= ~0x10; 
    if(ByteAnd[4] & ( 1 << 15 )) inBuff[0] |= 0x20; else if(!(ByteOr[4] & ( 1 << 15 ))) inBuff[0] &= ~0x20; 
    if(ByteAnd[1] & ( 1 << 10 )) inBuff[0] |= 0x40; else if(!(ByteOr[1] & ( 1 << 10 ))) inBuff[0] &= ~0x40; 
    if(ByteAnd[1] & ( 1 << 11 )) inBuff[0] |= 0x80; else if(!(ByteOr[1] & ( 1 << 11 ))) inBuff[0] &= ~0x80; 
    
    /* IN9 ~ IN16 */
    if(ByteAnd[1] & ( 1 << 12 )) inBuff[1] |= 0x01; else if(!(ByteOr[1] & ( 1 << 12 ))) inBuff[1] &= ~0x01; 
    if(ByteAnd[1] & ( 1 << 13 )) inBuff[1] |= 0x02; else if(!(ByteOr[1] & ( 1 << 13 ))) inBuff[1] &= ~0x02; 
    if(ByteAnd[1] & ( 1 << 14 )) inBuff[1] |= 0x04; else if(!(ByteOr[1] & ( 1 << 14 ))) inBuff[1] &= ~0x04; 
    if(ByteAnd[1] & ( 1 << 15 )) inBuff[1] |= 0x08; else if(!(ByteOr[1] & ( 1 << 15 ))) inBuff[1] &= ~0x08; 
    if(ByteAnd[3] & ( 1 << 8 )) inBuff[1] |= 0x10; else if(!(ByteOr[3] & ( 1 << 8 ))) inBuff[1] &= ~0x10; 
    if(ByteAnd[3] & ( 1 << 9 )) inBuff[1] |= 0x20; else if(!(ByteOr[3] & ( 1 << 9 ))) inBuff[1] &= ~0x20; 
    if(ByteAnd[3] & ( 1 << 10 )) inBuff[1] |= 0x40; else if(!(ByteOr[3] & ( 1 << 10 ))) inBuff[1] &= ~0x40; 
    if(ByteAnd[3] & ( 1 << 11 )) inBuff[1] |= 0x80; else if(!(ByteOr[3] & ( 1 << 11 ))) inBuff[1] &= ~0x80; 

    /* IN17 ~ IN24 */
    if(ByteAnd[3] & ( 1 << 12 )) inBuff[2] |= 0x01; else if(!(ByteOr[3] & ( 1 << 12 ))) inBuff[2] &= ~0x01; 
    if(ByteAnd[3] & ( 1 << 13 )) inBuff[2] |= 0x02; else if(!(ByteOr[3] & ( 1 << 13 ))) inBuff[2] &= ~0x02; 
    if(ByteAnd[3] & ( 1 << 14 )) inBuff[2] |= 0x04; else if(!(ByteOr[3] & ( 1 << 14 ))) inBuff[2] &= ~0x04; 
    if(ByteAnd[3] & ( 1 << 15 )) inBuff[2] |= 0x08; else if(!(ByteOr[3] & ( 1 << 15 ))) inBuff[2] &= ~0x08; 
    if(ByteAnd[2] & ( 1 << 6 )) inBuff[2] |= 0x10; else if(!(ByteOr[2] & ( 1 << 6 ))) inBuff[2] &= ~0x10; 
    if(ByteAnd[2] & ( 1 << 7 )) inBuff[2] |= 0x20; else if(!(ByteOr[2] & ( 1 << 7 ))) inBuff[2] &= ~0x20; 
    if(ByteAnd[2] & ( 1 << 8 )) inBuff[2] |= 0x40; else if(!(ByteOr[2] & ( 1 << 8 ))) inBuff[2] &= ~0x40; 
    if(ByteAnd[2] & ( 1 << 9 )) inBuff[2] |= 0x80; else if(!(ByteOr[2] & ( 1 << 9 ))) inBuff[2] &= ~0x80;

    /* IN25 ~ IN32 */
    if(ByteAnd[0] & ( 1 << 8 )) inBuff[3] |= 0x01; else if(!(ByteOr[0] & ( 1 << 8 ))) inBuff[3] &= ~0x01; 
    if(ByteAnd[2] & ( 1 << 10 )) inBuff[3] |= 0x02; else if(!(ByteOr[2] & ( 1 << 10 ))) inBuff[3] &= ~0x02; 
    if(ByteAnd[2] & ( 1 << 11 )) inBuff[3] |= 0x04; else if(!(ByteOr[2] & ( 1 << 11 ))) inBuff[3] &= ~0x04; 
    if(ByteAnd[2] & ( 1 << 12 )) inBuff[3] |= 0x08; else if(!(ByteOr[2] & ( 1 << 12 ))) inBuff[3] &= ~0x08; 
    if(ByteAnd[3] & ( 1 << 0 )) inBuff[3] |= 0x10; else if(!(ByteOr[3] & ( 1 << 0 ))) inBuff[3] &= ~0x10; 
    if(ByteAnd[3] & ( 1 << 1 )) inBuff[3] |= 0x20; else if(!(ByteOr[3] & ( 1 << 1 ))) inBuff[3] &= ~0x20; 
    if(ByteAnd[3] & ( 1 << 2 )) inBuff[3] |= 0x40; else if(!(ByteOr[3] & ( 1 << 2 ))) inBuff[3] &= ~0x40; 
    if(ByteAnd[3] & ( 1 << 3 )) inBuff[3] |= 0x80; else if(!(ByteOr[3] & ( 1 << 3 ))) inBuff[3] &= ~0x80;    
}

/*******************************************************************************
* Function Name  : output_driver
* Description    : Enable or disable relay output.
*                  
* Input          : out_buff: set the gpio pin value of data
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void output_driver(u8 out_buff[])
{
	if(out_buff[0] & 0x01) 		OTP1_ON(); 		else OTP1_OFF(); 					  
	if(out_buff[0] & 0x02) 		OTP2_ON(); 		else OTP2_OFF(); 	 					  
	if(out_buff[0] & 0x04) 		OTP3_ON(); 		else OTP3_OFF();	 					  
	if(out_buff[0] & 0x08)  	OCP1_ON(); 		else OCP1_OFF(); 						  
	if(out_buff[0] & 0x10)  	OCP2_ON(); 		else OCP2_OFF(); 					  
	if(out_buff[0] & 0x20)  	OCP3_ON(); 		else OCP3_OFF();				  
	if(out_buff[0] & 0x40)  	OCP4_ON(); 		else OCP4_OFF();				  
	if(out_buff[0] & 0x80)		OCP5_ON(); 		else OCP5_OFF(); 	
 
}

/*******************************************************************************
* Function Name  : Input_Output_PinInit
* Description    : Initializes the Input and Output GPIO
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void Input_Output_PinInit(void)
{
  
      GPIO_InitTypeDef GPIO_InitStruct;

#ifdef GEC_DBL1           
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
#else      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 
#endif

      /** input gpio ----------------------------------------------------- **/     
      /* IN1 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN2 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN3 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN4 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN5 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN6 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
      GPIO_Init(GPIOE , &GPIO_InitStruct);   

      /* IN7 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
      GPIO_Init(GPIOB , &GPIO_InitStruct);   

      /* IN8 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
      GPIO_Init(GPIOB , &GPIO_InitStruct);   

      /* IN9 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
      GPIO_Init(GPIOB , &GPIO_InitStruct);   

      /* IN10 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 

      /* IN11 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
      GPIO_Init(GPIOB , &GPIO_InitStruct);   

      /* IN12 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
      GPIO_Init(GPIOB , &GPIO_InitStruct);   

      /* IN13 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN14 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN15 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
      GPIO_Init(GPIOD , &GPIO_InitStruct);

      /* IN16 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
      GPIO_Init(GPIOD , &GPIO_InitStruct); 

      /* IN17 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN18 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN19 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN20 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN21 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
      GPIO_Init(GPIOC , &GPIO_InitStruct);

      /* IN22 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      /* IN23 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
      GPIO_Init(GPIOC , &GPIO_InitStruct);

      /* IN24 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      /* IN25 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
      GPIO_Init(GPIOA , &GPIO_InitStruct);

      /* IN26 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
      GPIO_Init(GPIOC , &GPIO_InitStruct);   

      /* IN27 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
      GPIO_Init(GPIOC , &GPIO_InitStruct);

      /* IN28 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
      GPIO_Init(GPIOC , &GPIO_InitStruct);

      /* IN29 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN30 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
      GPIO_Init(GPIOD , &GPIO_InitStruct);

      /* IN31 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
      GPIO_Init(GPIOD , &GPIO_InitStruct);   

      /* IN32 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
      GPIO_Init(GPIOD , &GPIO_InitStruct);


#ifdef GEC_DBL1       
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
#else
      GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
#endif      
      
      /** output gpio ----------------------------------------------------- **/ 
      /* OTP1 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 

      /* OTP2 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 

      /* OTP3 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
      GPIO_Init(GPIOB , &GPIO_InitStruct);        
      
      /* OCP1 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
      GPIO_Init(GPIOB , &GPIO_InitStruct);      

      /* OCP2 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 

      /* OCP3 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
      GPIO_Init(GPIOE , &GPIO_InitStruct); 

      /* OCP4 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 

      /* OCP5 */
      GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
      GPIO_Init(GPIOB , &GPIO_InitStruct); 
 
      OTP1_OFF();
      OTP2_OFF();
      OTP3_OFF();
      
      OCP1_OFF();
      OCP2_OFF();
      OCP3_OFF();
      OCP4_OFF();
      OCP5_OFF();
   
}

/*******************************************************************************
* Function Name  : SW_DP_Init
* Description    : Initializes the SW DP switch gpio.
*                  
* Input          : None
*                  None
* Output         : None
* Return         : None
*******************************************************************************/
void SW_DP_Init(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      
#ifdef GEC_DBL1 
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
      GPIO_Init(GPIOD, &GPIO_InitStructure);               
      
#else	 
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;				 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
      GPIO_Init(GPIOD, &GPIO_InitStructure);			
#endif   
   
}



/******************************  END OF FILE  *********************************/


