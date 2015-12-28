#include "sys.h"


void NVIC_Configuration(void)
{
  
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    
    INTX_ENABLE();

}

static u32 CpuID[3];
static u32 Lock_Code;


u32 GetLockCode(void)
{
//获取CPU唯一ID
CpuID[0]=*(vu32*)(0x1ffff7e8);
CpuID[1]=*(vu32*)(0x1ffff7ec);
CpuID[2]=*(vu32*)(0x1ffff7f0);
//加密算法,很简单的加密算法
Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);

//printf("CpuID[0] = %x\r\n",CpuID[0]);
//printf("CpuID[1] = %x\r\n",CpuID[1]);
//printf("CpuID[2] = %x\r\n",CpuID[2]);

return Lock_Code;
}


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM("WFI");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{
	__ASM("CPSID I");    		  
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM("CPSIE I");		  
}
//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(u32 addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

