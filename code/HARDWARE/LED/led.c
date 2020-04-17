#include "led.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
 GPIO_ResetBits(GPIOA,GPIO_Pin_All);
}
void displayonebit(u8 onebit){
unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
GPIO_Write(GPIOA,table[onebit]);
}
void chipenable(u8 chip)
{	
	switch(chip){
		case 0: GPIO_WriteBit(GPIOB, GPIO_Pin_0,Bit_SET);GPIO_WriteBit(GPIOB, GPIO_Pin_1,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_2,Bit_RESET);break;
		case 1: GPIO_WriteBit(GPIOB, GPIO_Pin_0,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_1,Bit_SET);GPIO_WriteBit(GPIOB, GPIO_Pin_2,Bit_RESET);break;
		case 2: GPIO_WriteBit(GPIOB, GPIO_Pin_0,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_1,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_2,Bit_SET);break;
		case 3: GPIO_WriteBit(GPIOB, GPIO_Pin_0,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_1,Bit_RESET);GPIO_WriteBit(GPIOB, GPIO_Pin_2,Bit_RESET);break;//close all cube
		default:break;
	}
}

void getNum(int num,int* arrdigits,int* digitnum){
	int i = 0;
	for(i=0;num>0;i++)
	   {
			 arrdigits[i] = num%10;
			 num=num/10;
		 }
	*digitnum = i;
}
void displayNumber(int number)
{
	static int status = 0;
	int arrdigits[3] = {0};
	int digitnum = 0;
	getNum(number,arrdigits,&digitnum);
	switch(status){
		case 0: chipenable(0);displayonebit(arrdigits[0]);status ++;break;
		case 4: chipenable(3);status ++;break;
		case 5: if(digitnum>1){chipenable(1);displayonebit(arrdigits[1]);}status ++;break;
		case 9: chipenable(3);status ++;break;
		case 10: if(digitnum>2){chipenable(2);displayonebit(arrdigits[2]);}status ++;break;
		case 14: chipenable(3);status = 0;break;
		default:status++;break;
	}
}
