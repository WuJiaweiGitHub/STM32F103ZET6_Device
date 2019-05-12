#ifndef __BEEP_H
#define __BEEP_H

#include <stm32f10x_conf.h>

/*****************����******************/
#define BEEP_TIM_GPIO_CLK 					(RCC_APB2Periph_GPIOB)
#define BEEP_OUT_PORT 							GPIOB
#define BEEP_OUT_PIN 								GPIO_Pin_14

/*****************״̬����******************/
#define BEEP_OPEN										GPIO_SetBits(BEEP_OUT_PORT, BEEP_OUT_PIN)
#define BEEP_CLOSE									GPIO_ResetBits(BEEP_OUT_PORT, BEEP_OUT_PIN)

void BEEP_Init(void);//��ʼ��

#endif
