#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "menu.h"

uint8_t Mode_zize = 0; //1：计时  2：闹钟 3：校准
uint8_t Num1[3] = {0,0,0};
uint8_t Num2[3] = {0,0,0};//闹钟数组
uint8_t Time_zize = 0;

extern uint8_t Clock_num;
extern uint16_t MyRTC_Time[];

/**
  * 函    数：按键中断初始化 PA0 PA2 PA6 PB0 PB11
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);		//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将引脚初始化为上拉输入
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将引脚初始化为上拉输入
	
	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);


	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure;						//定义结构体变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;					//选择配置外部中断的11号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;					//选择配置外部中断的11号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;					//选择配置外部中断的11号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;					//选择配置外部中断的11号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;					//选择配置外部中断的11号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
}



/**
  * 函    数：EXTI15_10外部中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void EXTI15_10_IRQHandler(void)
{
	
	if (EXTI_GetITStatus(EXTI_Line11) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
		{
      if(Mode_zize == 1)
			{
				Clock_num = 0;
			}
			
		}
		EXTI_ClearITPendingBit(EXTI_Line11);		//清除外部中断11号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)  // 检查是否是 PB0 的中断
    {
			Delay_ms(20);		
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)			//读PB0输入寄存器的状态，如果为0，则代表按键2按下
			{
		    taskIndex = taskTable[taskIndex].Enter;			
			}
        EXTI_ClearITPendingBit(EXTI_Line0);  // 清除中断挂起位
    }
}

void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)  // 检查是否是 PB0 的中断
    {
			Delay_ms(20);		
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)			//读PB0输入寄存器的状态，如果为0，则代表按键2按下
			{
		    taskIndex = taskTable[taskIndex].Next;	
			}
        EXTI_ClearITPendingBit(EXTI_Line2);  // 清除中断挂起位
    }
}

void EXTI9_5_IRQHandler(void)
{
	
	if (EXTI_GetITStatus(EXTI_Line5) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
		{
			if(Mode_zize == 1)
			{
				TIM_Cmd(TIM2, ENABLE);
			}
			//闹钟模式
			if(Mode_zize == 2)
			{
				Time_zize++;
			}
			//校准
			if(Mode_zize == 3)
			{
				MyRTC_Time[taskIndex-9]++;
			}
		}
			EXTI_ClearITPendingBit(EXTI_Line5);	
	}
	if (EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
		{
			if(Mode_zize == 1)
			{
				TIM_Cmd(TIM2, DISABLE);
			}
      //闹钟模式
			if(Mode_zize == 2)
			{
				if(Time_zize == 1)
				{
			    Num2[1]++;
				}
				if(Time_zize == 2)
				{
			    Num2[2]++;
				}
				if(Time_zize == 0)
				{
			    Num2[0]++;
				}
				if(Num2[0] == 25)
					Num2[0] = 0;
				if(Num2[1] == 61)
					Num2[1] = 0;
				if(Num2[2] == 61)
					Num2[2] = 0;
			}
			if(Mode_zize == 3)
			{
				MyRTC_Time[taskIndex-9]--;
			}			
		}
	
		EXTI_ClearITPendingBit(EXTI_Line7);
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}

