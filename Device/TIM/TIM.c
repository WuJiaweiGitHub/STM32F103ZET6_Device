#include "TIM.h"

void TIMxPWM_Init(Tim_OC* TIMx)//初始化
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	if(TIM2 == TIMx -> m_timx.TIMx)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		
		#if TIM2_PWM_OC_NO_REMAP//无映射
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}	
		
		#endif /*TIM2_PWM_OC_NO_REMAP*/
		
		#if TIM2_PWM_OC_PARTIALREMAP1//部分映射1
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}	
		
		#endif /*TIM2_PWM_OC_PARTIALREMAP1*/
		
		#if TIM2_PWM_OC_PARTIALREMAP2//部分映射2
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}	
		
		#endif /*TIM2_PWM_OC_PARTIALREMAP2*/
		
		#if TIM2_PWM_OC_FULLREMAP//全映射
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}	
		
		#endif /*TIM2_PWM_OC_FULLREMAP*/
	}
	
	if(TIM3 == TIMx -> m_timx.TIMx)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
		#if TIM3_PWM_OC_NO_REMAP
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}	
		
		#endif /*TIM3_PWM_OC_NO_REMAP*/
		
		#if TIM3_PWM_OC_PARTIALREMAP
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}	
		
		#endif /*TIM3_PWM_OC_PARTIALREMAP*/
		
		#if TIM3_PWM_OC_FULLREMAP
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		}	
		
		#endif /*TIM3_PWM_OC_FULLREMAP*/	
	}
	
	if(TIM4 == TIMx -> m_timx.TIMx)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		
		#if TIM4_PWM_OC_NO_REMAP
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		}	
		
		#endif /*TIM4_PWM_OC_NO_REMAP*/
		
		#if TIM4_PWM_OC_FULLREMAP
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
		
		GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		}
		
		if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
		{
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		}	
		
		#endif /*TIM4_PWM_OC_FULLREMAP*/
	}
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = TIMx ->m_timx.TIM_Arr - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIMx ->m_timx.TIM_Psc - 1;
	TIM_TimeBaseInit(TIMx -> m_timx.TIMx, &TIM_TimeBaseInitStruct);
	
	if (TIM_PWM_OC1_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC1_OPEN))
	{
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_Pulse = TIMx -> tim_pulse;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC1Init(TIMx -> m_timx.TIMx, &TIM_OCInitStruct);
		
		TIM_OC1PreloadConfig(TIMx ->m_timx.TIMx, TIM_OCPreload_Enable);
	}
	
	if (TIM_PWM_OC2_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC2_OPEN))
	{
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_Pulse = TIMx -> tim_pulse;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC2Init(TIMx -> m_timx.TIMx, &TIM_OCInitStruct);
		
		TIM_OC2PreloadConfig(TIMx ->m_timx.TIMx, TIM_OCPreload_Enable);
	}
	
	if (TIM_PWM_OC3_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC3_OPEN))
	{
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_Pulse = TIMx -> tim_pulse;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC3Init(TIMx -> m_timx.TIMx, &TIM_OCInitStruct);
		
		TIM_OC3PreloadConfig(TIMx ->m_timx.TIMx, TIM_OCPreload_Enable);
	}
	
	if (TIM_PWM_OC4_OPEN == (TIMx ->m_oc_init & TIM_PWM_OC4_OPEN))
	{
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStruct.TIM_Pulse = TIMx -> tim_pulse;
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC4Init(TIMx -> m_timx.TIMx, &TIM_OCInitStruct);
		
		TIM_OC4PreloadConfig(TIMx ->m_timx.TIMx, TIM_OCPreload_Enable);
	}
		
	TIM_Cmd(TIMx -> m_timx.TIMx, ENABLE);
}

/**
  * @brief  能够对不同通道的 PWM 调节占空比大小.
  * @param  TIMx:定时器名称. x (2 ~ 4) 
  * @param  TIM_SetCompare: 通道号.
  *   This parameter can be one of the following values:
  *     @arg OC1							: 通道1
  *     @arg OC2							: 通道2
  *     @arg OC3							: 通道3
  *     @arg OC4							: 通道4
  * @param  Compare1:  占空比大小值.
  * @retval None
  */
void TIMxPWM_SetDuty(TIM_TypeDef* TIMx, void (*TIM_SetCompare)(TIM_TypeDef*, uint16_t), uint16_t Compare)
{
	TIM_SetCompare(TIMx, Compare);
}
