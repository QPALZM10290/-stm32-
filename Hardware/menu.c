#include "stm32f10x.h"   
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MyRTC.h"
#include "menu.h"
#include "OLED.h"

uint8_t taskIndex = 0;	

extern uint8_t Num[3];
extern uint8_t Mode_zize;
extern uint8_t Num2[3];
extern uint16_t Clock_num2;


Menu_table_t taskTable[] =
{
    //一级界面
    {0, 1, 2, Menu_Interface}, 
    //二级界面
    {1, 0, 1, Function_Interface1},
    {2, 5, 3, Function_Interface2},
    {3, 6, 4, Function_Interface3},	
		{4, 9, 0, Function_Interface4},
		//三级界面
		{5, 0, 5, Function_Interface5},
		{6, 7, 8, Function_Interface6},
		{7, 1, 1, Function_Interface7},
		{8, 0, 6, Function_Interface8},
		{9, 9, 10, Function_Interface9},
		
		//校准界面
		{10, 10, 11, Function_Interface10},
		{11, 11, 12, Function_Interface11},
		{12, 12, 13, Function_Interface12},
		{13, 13, 14, Function_Interface13},
		{14, 14, 15, Function_Interface14},
		{15, 16, 17, Function_Interface15},
		{16, 1, 1, Function_Interface16},//显示校准设置成功
		{17, 0, 9, Function_Interface17},
};


void Menu_Interface(void)
{
	OLED_Clear();
	Mode_zize = 0;
	OLED_ShowChinese(0, 0, "实时时钟");
	OLED_ShowChinese(0, 16, "计时");
	OLED_ShowChinese(0, 32, "闹钟");
	OLED_ShowChinese(0, 48, "校准");
	OLED_ReverseArea(0,0, 64, 16);
	OLED_Update();	
}


void Function_Interface1(void)
{
	OLED_Clear();
	MyRTC_ReadTime();
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	Week_show();
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(95,48, 32, 16);
	OLED_Update();
}
void Function_Interface2(void)
{
	OLED_Clear();
	OLED_ShowChinese(0, 0, "实时时钟");
	OLED_ShowChinese(0, 16, "计时");
	OLED_ShowChinese(0, 32, "闹钟");
	OLED_ShowChinese(0, 48, "校准");
	OLED_ReverseArea(0,16, 32, 16);
	OLED_Update();	
}
void Function_Interface3(void)
{
	OLED_Clear();
	OLED_ShowChinese(0, 0, "实时时钟");
	OLED_ShowChinese(0, 16, "计时");
	OLED_ShowChinese(0, 32, "闹钟");
	OLED_ShowChinese(0, 48, "校准");
	OLED_ReverseArea(0,32, 32, 16);
	OLED_Update();	
}

void Function_Interface4(void)
{
	OLED_Clear();
	OLED_ShowChinese(0, 0, "实时时钟");
	OLED_ShowChinese(0, 16, "计时");
	OLED_ShowChinese(0, 32, "闹钟");
	OLED_ShowChinese(0, 48, "校准");
	OLED_ReverseArea(0,48, 32, 16);
	OLED_Update();	
}
void Function_Interface5(void)
{  //开启定时器 
	OLED_Clear();
	Mode_zize = 1;
	Clock_num_trans();
	OLED_ShowString(0, 0, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, Num[0], 2, OLED_8X16);
	OLED_ShowNum(24, 0,Num[1], 2, OLED_8X16);
	OLED_ShowNum(48, 0, Num[2], 2, OLED_8X16);
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(95,48, 32, 16);
	OLED_Update();
}
void Function_Interface6(void)
{
	OLED_Clear();
	Mode_zize = 2;
	OLED_ShowChinese(0, 0, "闹钟");
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 16, Num2[0], 2, OLED_8X16);
	OLED_ShowNum(24, 16,Num2[1], 2, OLED_8X16);
	OLED_ShowNum(48, 16, Num2[2], 2, OLED_8X16);	
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(0,32, 32, 16);
	OLED_Update();
}

void Function_Interface7(void)//显示闹钟设置成功
{
	OLED_Clear();
	Clock_num2 = Num2[0]*3600 + Num2[1]*60 + Num2[2];
	RTC_ITConfig(RTC_IT_SEC,ENABLE);//使能闹钟中断
	OLED_ShowChinese(0, 0, "闹钟设置成功");
	OLED_Update();
}
void Function_Interface8(void)
{
	OLED_Clear();
	OLED_ShowChinese(0, 0, "闹钟");
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 16, Num2[0], 2, OLED_8X16);
	OLED_ShowNum(24, 16,Num2[1], 2, OLED_8X16);
	OLED_ShowNum(48, 16, Num2[2], 2, OLED_8X16);	
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(95,48, 32, 16);
	OLED_Update();
}

void Function_Interface9(void)//修改数组
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	Mode_zize = 3;
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(0,0, 32, 16);
	OLED_Update();
}

void Function_Interface10(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(40,0, 16, 16);
	OLED_Update();
}
void Function_Interface11(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(64,0, 16, 16);
	OLED_Update();	
}
void Function_Interface12(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(0,16, 16, 16);
	OLED_Update();	
}
void Function_Interface13(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(24,16, 16, 16);
	OLED_Update();	
}
void Function_Interface14(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(48,16, 16, 16);
	OLED_Update();	
}
void Function_Interface15(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(0,32, 32, 16);
	OLED_Update();	
}

void Function_Interface16(void)//校准成功
{
	OLED_Clear();
	OLED_ShowChinese(0, 0, "校准成功");
	MyRTC_SetTime();
	OLED_Update();	
}
void Function_Interface17(void)
{
	OLED_Clear();
	OLED_ShowChinese(95, 0, "校准");
	OLED_ShowString(0, 0, "XXXX-XX-XX", OLED_8X16);
	OLED_ShowString(0, 16, "XX:XX:XX", OLED_8X16);
	OLED_ShowNum(0, 0, MyRTC_Time[0], 4, OLED_8X16);
	OLED_ShowNum(40, 0, MyRTC_Time[1], 2, OLED_8X16);
	OLED_ShowNum(64, 0, MyRTC_Time[2], 2, OLED_8X16);
	OLED_ShowNum(0, 16, MyRTC_Time[3], 2, OLED_8X16);
	OLED_ShowNum(24, 16, MyRTC_Time[4], 2, OLED_8X16);
	OLED_ShowNum(48, 16, MyRTC_Time[5], 2, OLED_8X16);
	OLED_ShowChinese(0, 32, "设置");
	OLED_ShowChinese(95, 48, "菜单");
	OLED_ReverseArea(95,48, 32, 16);
	OLED_Update();	
}
