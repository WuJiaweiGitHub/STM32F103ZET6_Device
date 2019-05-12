#include "SG90.h"

void SG90Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SG90_TIM_APBxClock_FUN(SG90_TIM_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(SG90_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = SG90_TIM_OUT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SG90_TIM_OUT_PORT, &GPIO_InitStruct);

	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = SG90_TIM_ARR - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = SG90_TIM_PSC - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(SG90_TIMx, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode =  SG90_TIM_OCMode;
	TIM_OCInitStruct.TIM_OCPolarity = SG90_TIM_OCPolarity;
	SG90_TIM_OCxInit(SG90_TIMx, &TIM_OCInitStruct);
 
  SG90_TIM_OCxPreloadConfig(SG90_TIMx, TIM_OCPreload_Enable);
        
  TIM_Cmd(SG90_TIMx, ENABLE);
	setAngle(0);
}
	
void setAngle(double angle)
{
	uint16_t temp = 0;
	
	temp = (((angle / 90 + 0.5) / 20) * SG90_TIM_ARR);
	SG90_TIM_SETCOMPAREX(SG90_TIMx, temp);
}

