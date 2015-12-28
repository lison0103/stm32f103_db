/****************************************Copyright (c)****************************************************
** File Name:           main.c
** Created By:          lisonchen
** Created date:        2015-12-22
** Version:             v0.1
** Descriptions:        stm32f103xb
** Last Update:         2015-12-28           
*********************************************************************************************************/

#include "sys.h"
#include "delay.h"   
#include "led.h"
#include "ewdt.h"
#include "digital_led.h"


int main(void)
{ 
        //����ϵͳ�ж����ȼ�����2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        
        delay_init();
        
        //�ⲿ���Ź���ʼ��
//        EWDT_Drv_pin_config();
//        power_on_bsp_check();
        
        //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED_Init();	
        
        //DB�����¶˵�ַѡ���ʼ��
        SW_DP_Init();
//        ReadSwDp();
        
        //����ܳ�ʼ��
        digital_led_gpio_init();               
        digital_led_check();        
}
	   



