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
	u8 mode=CAN_Mode_Normal;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

	 	
   
	CAN_Mode_Init(CAN_SJW_2tq,CAN_BS2_5tq,CAN_BS1_3tq,20,mode);//CAN��ʼ������ģʽ,������500Kbps    

	
 	while(1)
	{

#if 0
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
//				printf("%s",canbuf[i]);	//��ʾ����

 			}
			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)
			{}
                        else
                          delay_ms(10);
                        

#else		 
		can_rcv=Can_Receive_Msg(canbuf);
		if(can_rcv)//���յ�������
		{			
			
 			for(i=0;i<can_rcv;i++)
			{									    
//				printf("%s",canbuf[i]);	//��ʾ����
 			}
		}
#endif                
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//��ʾϵͳ��������	
			t=0;
			cnt++;
		}		   
	}
}


int main(void)
{ 
        //����ϵͳ�ж����ȼ�����2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        
        delay_init();
        
        
        //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED_Init();	
        
        //DB�����¶˵�ַѡ���ʼ��
//        SW_DP_Init();
//        ReadSwDp();
        
        //����ܳ�ʼ��
        digital_led_gpio_init();               
        digital_led_check();       
        
        
        //can����
        can_test();
        
//        HW_TEST_INIT();
//        HW_TEST();
        
}
	   



