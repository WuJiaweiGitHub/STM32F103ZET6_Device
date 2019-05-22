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
	TIM_TypeDef* TIMx;//��ʱ��
	uint16_t TIM_Psc;//Ԥ��Ƶϵ��
	uint16_t TIM_Arr;//�Զ���װ�ؼĴ���ֵ
}Tim;

typedef struct Tim_OC
{
	Tim m_timx;//��ʱ����ʼ������
	unsigned char m_oc_init;//ͨ����ʼ��ѡ��
	uint16_t tim_pulse;//�����˴�װ�벶��ȽϼĴ���������ֵ
}Tim_OC;

void TIMxPWM_Init(Tim_OC* TIMx);//��ʼ��
//�ܹ��Բ�ͬͨ���� PWM ����ռ�ձȴ�С.
void TIMxPWM_SetDuty(TIM_TypeDef* TIMx, void (*TIM_SetCompare)(TIM_TypeDef*, uint16_t), uint16_t Compare1);

#endif
