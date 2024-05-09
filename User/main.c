#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "MyRTC.h"
#include "menu.h"



int main(void)
{
	OLED_Power(); //给OLED供电
	Key_Init();
	OLED_Init();
	MyRTC_Init();
	Timer_Init();
	Timer_TM3_Init();
  SecEXTI_Init();
	
	while (1)
	{
		taskTable[taskIndex].Current_Operation();//执行函数
	}
}
