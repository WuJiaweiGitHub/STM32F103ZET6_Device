#include "KEYEXTI.h"

void KEYEXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK | KEY0_INT_GPIO_CLK, ENABLE);

/***************************配置KEY1**********************************/	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = KEY1_INT_EXTI_LINE;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
/***************************配置KEY0**********************************/
	GPIO_InitStruct.GPIO_Pin = KEY0_INT_GPIO_PIN;
	GPIO_Init(KEY0_INT_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY0_INT_EXTI_PORTSOURCE, KEY0_INT_EXTI_PINSOURCE);

	EXTI_InitStruct.EXTI_Line = KEY0_INT_EXTI_LINE;
	EXTI_Init(&EXTI_InitStruct);
	
	KEYEXTI_InitNVIC();
}

static void KEYEXTI_InitNVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

//配置中断分组
#ifndef SET_NVIC_GROUP
#define SET_NVIC_GROUP
	NVIC_PriorityGroupConfig(NVIC_GROUP);
#endif /*SET_NVIC_GROUP*/
	
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = KEY1_IRQChannelPreemptionPriority;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = KEY1_NVIC_IRQChannelSubPriority;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = KEY0_IRQChannelPreemptionPriority;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = KEY0_NVIC_IRQChannelSubPriority;
	NVIC_Init(&NVIC_InitStruct);
}

extern unsigned char brightnessLevel;

//亮度增加
void KEY1_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET)
	{
		delay_ms(10);
		if(!KEY1_INT_GPIO_STAT)
		{
			while(!KEY1_INT_GPIO_STAT);
			
			if(4 <= brightnessLevel)
			{
				brightnessLevel = 4;
			}else
			{
				brightnessLevel++;
			}
		}

		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
	}
}

//亮度减少
void KEY0_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY0_INT_EXTI_LINE) != RESET)
	{
		delay_ms(10);
		if(!KEY0_INT_GPIO_STAT)
		{
			while(!KEY0_INT_GPIO_STAT);
			if(0 >= brightnessLevel)
			{
				brightnessLevel = 0;
			}else
			{
				brightnessLevel--;
			}
		
		}
		EXTI_ClearITPendingBit(KEY0_INT_EXTI_LINE);
	}
}
