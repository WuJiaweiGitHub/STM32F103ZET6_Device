#ifndef __STEERENGINE_H
#define __STEERENGINE_H

#include <stm32f10x_conf.h>
#include "TIM.h"

//****************��ʱ������************************/
#define STEERENGINE_TIMx 										TIM2
#define STEERENGINE_TIM_ARR 								20000
#define STEERENGINE_TIM_PSC 								72
#define STEERENGINE_TIM_Pulse 							(((0 / 90 + 0.5) / 20) * STEERENGINE_TIM_ARR)
#define STEERENGINE_TIM_CHECK_OC 						TIM_PWM_OC1_OPEN

//****************ͨ��ѡ�� 1~4************************/
#define STEERENGINE_TIM_OCx 								OC1 


void STEERENGINE_Init(void);//��ʼ��
void STEERENGINE_Drive(double angle);//���ýǶ�(ȡֵ0~180)

#endif /*__STEERENGINE_H*/
