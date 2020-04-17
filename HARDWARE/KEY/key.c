#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

u8 KEY0_Scan(void)
{	 
	static u8 status = 0;
	static u32 longpress = 0;
	switch(status){
		case 0:if(KEY0 == 0) status = 1;break;
		case 1:if(KEY0 == 0) status = 2;else status = 0; break;
		case 2:if(KEY0 == 1){status = 0;day += 1;}else longpress++; if(longpress >= 20)status = 3; break;
		case 3:if(KEY0 == 0) {longpress++;if(longpress >= 20){longpress = 0;day+=1;}}else status = 0; break;
	}
	
}
u8 KEY1_Scan(void)
{	 
	static u8 status = 0;
	static u32 longpress = 0;
	switch(status){
		case 0:if(KEY1 == 0) status = 1;break;
		case 1:if(KEY1 == 0) status = 2;else status = 0; break;
		case 2:if(KEY1 == 1){status = 0;day -= 1;}else longpress++; if(longpress >= 20)status = 3; break;
		case 3:if(KEY1 == 0) {longpress++;if(longpress >= 20){longpress = 0;day-=1;}}else status = 0; break;
		
	}
	
}
