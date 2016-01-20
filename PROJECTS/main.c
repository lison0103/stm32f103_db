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
	u8 mode=CAN_Mode_LoopBack;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

	 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    

	
 	while(1)
	{

		if(mode==CAN_Mode_LoopBack)//KEY0����,����һ������
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
				if(i<4)printf("%s",canbuf[i]);	//��ʾ����
				else printf("%s",canbuf[i]);	//��ʾ����
 			}
			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)printf("Failed");		//��ʾ����ʧ��
			else printf("OK    ");	 		//��ʾ���ͳɹ�								   
		}else if(mode==CAN_Mode_Normal)//WK_UP���£��ı�CAN�Ĺ���ģʽ
		{	   
//			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN��ͨģʽ��ʼ��, ������500Kbps 

			if(mode==0)//��ͨģʽ����Ҫ2��������
			{
				printf("Nnormal Mode ");	    
			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
			{
 				printf("LoopBack Mode");
			}

		}		 
		can_rcv=Can_Receive_Msg(canbuf);
		if(can_rcv)//���յ�������
		{			
			
 			for(i=0;i<can_rcv;i++)
			{									    
				if(i<4)printf("%s",canbuf[i]);	//��ʾ����
				else printf("%s",canbuf[i]);	//��ʾ����
 			}
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//��ʾϵͳ��������	
			t=0;
			cnt++;
			printf("%d",cnt);	//��ʾ����
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
        SW_DP_Init();
//        ReadSwDp();
        
        //����ܳ�ʼ��
        digital_led_gpio_init();               
        digital_led_check();       
        
        
        //can����
//        can_test();
        
        HW_TEST_INIT();
        HW_TEST();
        
}
	   



