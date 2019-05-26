#include "RGBLED.h"

void RGBLED_Init(void)
{
	
#ifdef COLOR_PWM_GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	COLOR_TIM_APBxClock_FUN(COLOR_TIM_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(COLOR_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = COLOR_RED_TIM_LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = COLOR_GREEN_TIM_LED_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = COLOR_BLUE_TIM_LED_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = COLOR_TIM_ARR - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler  = COLOR_TIM_PSC - 1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(COLOR_TIMx, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = COLOR_RED_TIM_OCMode;
	TIM_OCInitStruct.TIM_OCPolarity = COLOR_RED_TIM_OCPolarity;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable ;
	COLOR_RED_TIM_OCxInit(COLOR_TIMx, &TIM_OCInitStruct);
	
	
	TIM_OCInitStruct.TIM_OCMode = COLOR_GREEN_TIM_OCMode;
	TIM_OCInitStruct.TIM_OCPolarity = COLOR_GREEN_TIM_OCPolarity;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable ;
	COLOR_GREEN_TIM_OCxInit(COLOR_TIMx, &TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = COLOR_BLUE_TIM_OCMode;
	TIM_OCInitStruct.TIM_OCPolarity = COLOR_BLUE_TIM_OCPolarity;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable ;
	COLOR_BLUE_TIM_OCxInit(COLOR_TIMx, &TIM_OCInitStruct);
	
	COLOR_RED_TIM_OCxPreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);
	COLOR_GREEN_TIM_OCxPreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);
	COLOR_BLUE_TIM_OCxPreloadConfig(COLOR_TIMx, TIM_OCPreload_Enable);
	
	TIM_Cmd(COLOR_TIMx, ENABLE);
	
	LED_RGBOFF;
#endif
	
#ifdef COLOR_GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(COLOR_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = COLOR_RED_TIM_LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = COLOR_GREEN_TIM_LED_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = COLOR_BLUE_TIM_LED_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	LED_RGBOFF;
#endif

}

#ifdef COLOR_PWM_GPIO
void setCloroRGB(unsigned int red, unsigned int green, unsigned int bule)
{
	COLOR_RED_TIM_SETCOMPAREX(COLOR_TIMx, red);
	COLOR_GREEN_TIM_SETCOMPAREX(COLOR_TIMx, green);
	COLOR_BLUE_TIM_SETCOMPAREX(COLOR_TIMx, bule);
}
#endif
