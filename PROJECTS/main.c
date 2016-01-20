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
#include "can.h"
#include "hw_test.h"


void can_test(void)
 {	 
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
        u8 can_rcv;
	u8 mode=CAN_Mode_LoopBack;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式

	 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率500Kbps    

	
 	while(1)
	{

		if(mode==CAN_Mode_LoopBack)//KEY0按下,发送一次数据
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//填充发送缓冲区
				if(i<4)printf("%s",canbuf[i]);	//显示数据
				else printf("%s",canbuf[i]);	//显示数据
 			}
			res=Can_Send_Msg(canbuf,8);//发送8个字节 
			if(res)printf("Failed");		//提示发送失败
			else printf("OK    ");	 		//提示发送成功								   
		}else if(mode==CAN_Mode_Normal)//WK_UP按下，改变CAN的工作模式
		{	   
//			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN普通模式初始化, 波特率500Kbps 

			if(mode==0)//普通模式，需要2个开发板
			{
				printf("Nnormal Mode ");	    
			}else //回环模式,一个开发板就可以测试了.
			{
 				printf("LoopBack Mode");
			}

		}		 
		can_rcv=Can_Receive_Msg(canbuf);
		if(can_rcv)//接收到有数据
		{			
			
 			for(i=0;i<can_rcv;i++)
			{									    
				if(i<4)printf("%s",canbuf[i]);	//显示数据
				else printf("%s",canbuf[i]);	//显示数据
 			}
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//提示系统正在运行	
			t=0;
			cnt++;
			printf("%d",cnt);	//显示数据
		}		   
	}
}


int main(void)
{ 
        //设置系统中断优先级分组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        
        delay_init();
        
        
        //初始化与LED连接的硬件接口
	LED_Init();	
        
        //DB板上下端地址选择初始化
        SW_DP_Init();
//        ReadSwDp();
        
        //数码管初始化
        digital_led_gpio_init();               
        digital_led_check();       
        
        
        //can测试
//        can_test();
        
        HW_TEST_INIT();
        HW_TEST();
        
}
	   



