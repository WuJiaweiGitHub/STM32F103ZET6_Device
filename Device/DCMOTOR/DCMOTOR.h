#ifndef __DCMOTOR_H
#define __DCMOTOR_H

#include <stm32f10x_conf.h>
#include "TIM.h"

/************����ӿ�IN1***************/
#define MOTOR_IN1_PORT 											GPIOB
#define MOTOR_IN1_PIN 											GPIO_Pin_6
#define MOTOR_IN1_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************����ӿ�IN2***************/
#define MOTOR_IN2_PORT 											GPIOB
#define MOTOR_IN2_PIN 											GPIO_Pin_7
#define MOTOR_IN2_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************����ӿ�IN3***************/
#define MOTOR_IN3_PORT 											GPIOB
#define MOTOR_IN3_PIN 											GPIO_Pin_8
#define MOTOR_IN3_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************����ӿ�IN4***************/
#define MOTOR_IN4_PORT 											GPIOB
#define MOTOR_IN4_PIN 											GPIO_Pin_9
#define MOTOR_IN4_GPIO_CLK 									RCC_APB2Periph_GPIOB

//****************ENA����************************/
#define MOTOR_ENA_TIMx 										TIM2
#define MOTOR_ENA_TIM_ARR 								20000
#define MOTOR_ENA_TIM_PSC 								72
#define MOTOR_ENA_TIM_Pulse 							MOTOR_ENA_TIM_ARR * 0

#define MOTOR_ENA_TIM_CHECK_OC 						TIM_PWM_OC2_OPEN
#define MOTOR_ENA_TIM_OCx 								OC2 

//****************ENB����************************/
#define MOTOR_ENB_TIMx 										TIM2
#define MOTOR_ENB_TIM_ARR 								20000
#define MOTOR_ENB_TIM_PSC 								72
#define MOTOR_ENB_TIM_Pulse 							MOTOR_ENA_TIM_ARR * 0

#define MOTOR_ENB_TIM_CHECK_OC 						TIM_PWM_OC3_OPEN
#define MOTOR_ENB_TIM_OCx 								OC3 

/***************************ɲ��***********************************/
//���1
#define MOTOR1_BRAKE												GPIO_ResetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_ResetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//���2
#define MOTOR2_BRAKE												GPIO_ResetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_ResetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)

/***************************��ת***********************************/
//���1
#define MOTOR1_FORWARD											GPIO_SetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_ResetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//���2
#define MOTOR2_FORWARD											GPIO_SetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_ResetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)


/***************************��ת***********************************/
//���1
#define MOTOR1_REVERSE											GPIO_ResetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_SetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//���2
#define MOTOR2_REVERSE											GPIO_ResetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_SetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)
																						
typedef enum Turn
{
	Forward = 0,//��ת
	Reverse			//��ת
}Turn;

typedef enum LR
{
	left = 0,//IN1,IN2(��)
	right		 //IN3,IN4(��)
}LR;

void DCMOTOR_Init(void);//��ʼ��
void DCMOTOR_Drive(LR lr, Turn turn, double en);//�����ٶ�

#endif
