#ifndef __DCMOTOR_H
#define __DCMOTOR_H

#include <stm32f10x_conf.h>
#include "TIM.h"

/************电机接口IN1***************/
#define MOTOR_IN1_PORT 											GPIOB
#define MOTOR_IN1_PIN 											GPIO_Pin_6
#define MOTOR_IN1_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************电机接口IN2***************/
#define MOTOR_IN2_PORT 											GPIOB
#define MOTOR_IN2_PIN 											GPIO_Pin_7
#define MOTOR_IN2_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************电机接口IN3***************/
#define MOTOR_IN3_PORT 											GPIOB
#define MOTOR_IN3_PIN 											GPIO_Pin_8
#define MOTOR_IN3_GPIO_CLK 									RCC_APB2Periph_GPIOB

/************电机接口IN4***************/
#define MOTOR_IN4_PORT 											GPIOB
#define MOTOR_IN4_PIN 											GPIO_Pin_9
#define MOTOR_IN4_GPIO_CLK 									RCC_APB2Periph_GPIOB

//****************ENA配置************************/
#define MOTOR_ENA_TIMx 										TIM2
#define MOTOR_ENA_TIM_ARR 								20000
#define MOTOR_ENA_TIM_PSC 								72
#define MOTOR_ENA_TIM_Pulse 							MOTOR_ENA_TIM_ARR * 0

#define MOTOR_ENA_TIM_CHECK_OC 						TIM_PWM_OC2_OPEN
#define MOTOR_ENA_TIM_OCx 								OC2 

//****************ENB配置************************/
#define MOTOR_ENB_TIMx 										TIM2
#define MOTOR_ENB_TIM_ARR 								20000
#define MOTOR_ENB_TIM_PSC 								72
#define MOTOR_ENB_TIM_Pulse 							MOTOR_ENA_TIM_ARR * 0

#define MOTOR_ENB_TIM_CHECK_OC 						TIM_PWM_OC3_OPEN
#define MOTOR_ENB_TIM_OCx 								OC3 

/***************************刹车***********************************/
//电机1
#define MOTOR1_BRAKE												GPIO_ResetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_ResetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//电机2
#define MOTOR2_BRAKE												GPIO_ResetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_ResetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)

/***************************正转***********************************/
//电机1
#define MOTOR1_FORWARD											GPIO_SetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_ResetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//电机2
#define MOTOR2_FORWARD											GPIO_SetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_ResetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)


/***************************反转***********************************/
//电机1
#define MOTOR1_REVERSE											GPIO_ResetBits(MOTOR_IN1_PORT, MOTOR_IN1_PIN); \
																						GPIO_SetBits(MOTOR_IN2_PORT, MOTOR_IN2_PIN)
//电机2
#define MOTOR2_REVERSE											GPIO_ResetBits(MOTOR_IN3_PORT, MOTOR_IN3_PIN); \
																						GPIO_SetBits(MOTOR_IN4_PORT, MOTOR_IN4_PIN)
																						
typedef enum Turn
{
	Forward = 0,//正转
	Reverse			//反转
}Turn;

typedef enum LR
{
	left = 0,//IN1,IN2(左)
	right		 //IN3,IN4(右)
}LR;

void DCMOTOR_Init(void);//初始化
void DCMOTOR_Drive(LR lr, Turn turn, double en);//设置速度

#endif
