#include "DCMOTOR.h"

void DCMOTOR_Init(void)
{
	Tim_OC tim;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(MOTOR_IN1_GPIO_CLK | MOTOR_IN2_GPIO_CLK |
												 MOTOR_IN3_GPIO_CLK | MOTOR_IN4_GPIO_CLK, 
												 ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = MOTOR_IN1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_IN1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MOTOR_IN2_PIN;
	GPIO_Init(MOTOR_IN2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MOTOR_IN3_PIN;
	GPIO_Init(MOTOR_IN3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MOTOR_IN4_PIN;
	GPIO_Init(MOTOR_IN4_PORT, &GPIO_InitStruct);
	
	tim.m_timx.TIMx = MOTOR_ENA_TIMx;
	tim.m_timx.TIM_Arr = MOTOR_ENA_TIM_ARR;
	tim.m_timx.TIM_Psc = MOTOR_ENA_TIM_PSC;
	tim.m_oc_init = MOTOR_ENA_TIM_CHECK_OC;
	tim.tim_pulse = MOTOR_ENA_TIM_Pulse;
	
	TIMxPWM_Init(&tim);
	
	tim.m_timx.TIMx = MOTOR_ENB_TIMx;
	tim.m_timx.TIM_Arr = MOTOR_ENB_TIM_ARR;
	tim.m_timx.TIM_Psc = MOTOR_ENB_TIM_PSC;
	tim.m_oc_init = MOTOR_ENB_TIM_CHECK_OC;
	tim.tim_pulse = MOTOR_ENB_TIM_Pulse;
	
	TIMxPWM_Init(&tim);
}

void DCMOTOR_Drive(LR lr, Turn turn, double en)
{
	unsigned int temp = 0;
	
	if (left == lr)//左侧电机
	{
		temp = MOTOR_ENA_TIM_ARR * en;
		
		if(10 >= temp)//刹车
		{
			MOTOR1_BRAKE;
			return ;
		}
		
		if(Forward == turn)//正转
		{
			MOTOR1_FORWARD;
			
		}else//反转
		{
			MOTOR1_REVERSE;
		}
		
		TIMxPWM_SetDuty(MOTOR_ENA_TIMx, MOTOR_ENA_TIM_OCx, temp);
	}else//右侧电机
	{
		temp = MOTOR_ENB_TIM_ARR * en;
		
		if(10 >= temp)//刹车
		{
			MOTOR2_BRAKE;
			return ;
		}
		
		if(Forward == turn)//正转
		{
			MOTOR2_FORWARD;
			
		}else
		{
			MOTOR2_REVERSE;
		}
		
		TIMxPWM_SetDuty(MOTOR_ENB_TIMx, MOTOR_ENB_TIM_OCx, temp);
	}
}
