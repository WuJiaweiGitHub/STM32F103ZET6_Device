#ifndef __TIM_H
#define __TIM_H

#include <stm32f10x_conf.h>

#define OC1 TIM_SetCompare1
#define OC2 TIM_SetCompare2
#define OC3 TIM_SetCompare3
#define OC4 TIM_SetCompare4

#define TIM_PWM_OC1_OPEN       			0x01
#define TIM_PWM_OC2_OPEN       			0x02
#define TIM_PWM_OC3_OPEN       			0x04
#define TIM_PWM_OC4_OPEN       			0x08

typedef struct Tim
{
	TIM_TypeDef* TIMx;//定时器
	uint16_t TIM_Psc;//预分频系数
	uint16_t TIM_Arr;//自动重装载寄存器值
}Tim;

typedef struct Tim_OC
{
	Tim m_timx;//定时器初始化配置
	unsigned char m_oc_init;//通道初始化选择
	uint16_t tim_pulse;//设置了待装入捕获比较寄存器的脉冲值
}Tim_OC;

void TIMxPWM_Init(Tim_OC* TIMx);//初始化
//能够对不同通道的 PWM 调节占空比大小.
void TIMxPWM_SetDuty(TIM_TypeDef* TIMx, void (*TIM_SetCompare)(TIM_TypeDef*, uint16_t), uint16_t Compare1);

#endif
