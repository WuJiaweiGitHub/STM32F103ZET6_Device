#ifndef __STEERINGGEAR_H
#define __STEERINGGEAR_H

#include <stm32f10x_conf.h>

#define SG90_TIM_APBxClock_FUN 			RCC_APB1PeriphClockCmd

//****************��ʱ������************************/
#define SG90_TIMx 									TIM3
#define SG90_TIM_ARR 								20000
#define SG90_TIM_PSC 								72
#define SG90_TIM_CLK 								RCC_APB1Periph_TIM3

//****************������Ŷ���************************/
#define SG90_TIM_OUT_PORT 					GPIOA
#define SG90_TIM_OUT_PIN 						GPIO_Pin_6
#define SG90_TIM_GPIO_CLK 					(RCC_APB2Periph_GPIOA)

//****************ͨ��ѡ�� 1~4************************/
#define SG90_TIM_OCxInit 						TIM_OC1Init 
#define SG90_TIM_OCxPreloadConfig 	TIM_OC1PreloadConfig
#define SG90_TIM_OCMode 						TIM_OCMode_PWM1
#define SG90_TIM_OCPolarity 				TIM_OCPolarity_High
#define SG90_TIM_SETCOMPAREX 				TIM_SetCompare1

void SG90Init(void);//��ʼ��
void setAngle(double angle);//�Ƕȸı�(0~180)

#endif
