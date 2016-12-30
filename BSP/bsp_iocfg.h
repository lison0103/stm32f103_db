/*******************************************************************************
* File Name          : bsp_iocfg.h
* Author             : lison
* Version            : V1.0
* Date               : 04/15/2016
* Description        : Contains prototype of input and output pin Initializes.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_IOCFG_H
#define __BSP_IOCFG_H

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Input_Output_PinInit(void);
void SW_DP_Init(void);
void Get_GpioInput(u8 inBuff[]);
void output_driver(u8 out_buff[]);
u8 ReadSwDp(void);

//INPUT
#define IN1     PEin(10)
#define IN2     PEin(11)
#define IN3     PEin(12)
#define IN4     PEin(13)
#define IN5     PEin(14)
#define IN6     PEin(15)
#define IN7     PBin(10)
#define IN8     PBin(11)
#define IN9     PBin(12)
#define IN10     PBin(13)
#define IN11     PBin(14)
#define IN12     PBin(15)
#define IN13     PDin(8)
#define IN14     PDin(9)
#define IN15     PDin(10)
#define IN16     PDin(11)
#define IN17     PDin(12)
#define IN18     PDin(13)
#define IN19     PDin(14)
#define IN20     PDin(15)
#define IN21     PCin(6)
#define IN22     PCin(7)
#define IN23     PCin(8)
#define IN24     PCin(9)
#define IN25     PAin(8)
#define IN26     PCin(10)
#define IN27     PCin(11)
#define IN28     PCin(12)
#define IN29     PDin(0)
#define IN30     PDin(1)
#define IN31     PDin(2)
#define IN32     PDin(3)

//OUTPUT
#define OTP1_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define OTP1_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define OTP2_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define OTP2_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define OTP3_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define OTP3_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define OCP1_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define OCP1_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define OCP2_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define OCP2_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define OCP3_ON()     GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define OCP3_OFF()     GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define OCP4_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define OCP4_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define OCP5_ON()     GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define OCP5_OFF()     GPIO_ResetBits(GPIOB,GPIO_Pin_8)



#endif /* __BSP_IOCFG_H */


/******************************  END OF FILE  *********************************/



