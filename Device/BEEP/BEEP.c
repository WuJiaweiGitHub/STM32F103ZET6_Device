#include "BEEP.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(BEEP_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = BEEP_OUT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BEEP_OUT_PORT, &GPIO_InitStruct);
	
	BEEP_CLOSE;
}
