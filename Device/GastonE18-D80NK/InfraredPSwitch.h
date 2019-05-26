#ifndef __INFRAREDPSWITCH_H
#define __INFRAREDPSWITCH_H

#include <stm32f10x_conf.h>

//***************���Ŷ���*********************/
#define E18_TIM_GPIO_CLK 					(RCC_APB2Periph_GPIOB)
#define E18_OUT_PORT 							GPIOB
#define E18_OUT_PIN 							GPIO_Pin_15

//***************״̬*********************/
#define CHECK_OBJECT       				1
#define NO_CHECK_OBJECT						0

/****************ȡ��״̬*****************/
#define E18_OUT_STAST							GPIO_ReadInputDataBit(E18_OUT_PORT, E18_OUT_PIN)

void InfraredPSwitch_Init(void);//��ʼ��
unsigned char InfraredPSwitch_Check(void);//״̬���

#endif
