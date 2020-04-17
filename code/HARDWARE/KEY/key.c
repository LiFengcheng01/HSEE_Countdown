#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
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
