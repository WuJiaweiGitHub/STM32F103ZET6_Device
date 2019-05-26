#include "STEERENGINE.h"

void STEERENGINE_Init(void)
{
	Tim_OC tim;
	
	tim.m_timx.TIMx = STEERENGINE_TIMx;
	tim.m_timx.TIM_Arr = STEERENGINE_TIM_ARR;
	tim.m_timx.TIM_Psc = STEERENGINE_TIM_PSC;
	tim.m_oc_init = STEERENGINE_TIM_CHECK_OC;
	tim.tim_pulse = STEERENGINE_TIM_Pulse;
	
	TIMxPWM_Init(&tim);
}

void STEERENGINE_Drive(double angle)
{
	uint16_t temp = 0;
	
	temp = (((angle / 90 + 0.5) / 20) * STEERENGINE_TIM_ARR);
	
	TIMxPWM_SetDuty(STEERENGINE_TIMx, STEERENGINE_TIM_OCx, temp);
}
