#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
#include "timer.h"

int main(void)
{
	u8 i = 0;
 	vu8 key=0;
	int arrdigits[3] = {0};
	int digitnum = 0;
	TIM3_Int_Init(999,71);//1ms
	delay_init();	    	 	  
 	LED_Init();			     
	KEY_Init();          


	
	while(1)
	{
		if(scan)
		{
			displayNumber(day);
			scan = 0;
		}
		if(keyscan)
		{
			KEY0_Scan();
			KEY1_Scan();
			keyscan = 0;
		}
 	}
}

