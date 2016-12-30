/*******************************************************************************
* File Name          : esc.h
* Author             : lison
* Version            : V1.0
* Date               : 08/01/2016
* Description        : This file contains esc parameters.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ESC_H
#define __ESC_H	

/* Includes ------------------------------------------------------------------*/
#include "includes.h"


/* Exported types ------------------------------------------------------------*/
typedef struct  
{
    /* Header code and comm times */
    u8 HeaderCode[6];
    
    /* swdp switch value */
    u8 SwdpAdr;
    
    /* Input data */
    u8 DBLInputData[4];
    
    /* Output data */
    u8 DBLOutputData;

    /* Error code */
    u16 ErrorCode;
    
	
}DBL1EscData;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define DBL1_UPPER_ADDR 0x55u
#define DBL1_LOWER_ADDR 0xaau
#define DBL1_INTERM1_ADDR 0x33u
#define DBL1_INTERM2_ADDR 0xddu
#define DBL1_TEST_MODE  0xfau

/* Exported functions ------------------------------------------------------- */
void CAN_Comm(void);
void esc_error_display(void);
void GetAdr(void);


/* ESC */
extern DBL1EscData EscData;

/* safety board data */
extern u8 EscDataToSafety[3][8];
extern u8 EscDataFromSafety[3][8];

#endif  /* __ESC_H */


/******************************  END OF FILE  *********************************/







