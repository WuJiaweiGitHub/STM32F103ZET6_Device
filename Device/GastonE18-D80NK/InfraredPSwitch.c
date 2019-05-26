#include "InfraredPSwitch.h"

void InfraredPSwitch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(E18_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = E18_OUT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(E18_OUT_PORT, &GPIO_InitStruct);
}
unsigned char InfraredPSwitch_Check(void)
{
	if(1 == E18_OUT_STAST)
	{
		return NO_CHECK_OBJECT;
	}else
	{
		return CHECK_OBJECT;
	}
}
