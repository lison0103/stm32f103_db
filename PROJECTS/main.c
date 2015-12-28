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
        //设置系统中断优先级分组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        
        delay_init();
        
        //外部看门狗初始化
//        EWDT_Drv_pin_config();
//        power_on_bsp_check();
        
        //初始化与LED连接的硬件接口
	LED_Init();	
        
        //DB板上下端地址选择初始化
        SW_DP_Init();
//        ReadSwDp();
        
        //数码管初始化
        digital_led_gpio_init();               
        digital_led_check();        
}
	   



