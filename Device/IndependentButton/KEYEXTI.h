#ifndef __KEYEXTI_H
#define __KEYEXTI_H

#include <stm32f10x_conf.h>

//延时函数
extern void delay_ms(u16 nms);

//引脚定义
/***************************配置KEY_1**********************************/	

#define KEY1_INT_GPIO_CLK 									(RCC_APB2Periph_GPIOE\
																						|RCC_APB2Periph_AFIO)
																					
#define KEY1_INT_GPIO_PORT 									GPIOE																					
#define KEY1_INT_GPIO_PIN 									GPIO_Pin_3

#define KEY1_INT_EXTI_PORTSOURCE 						GPIO_PortSourceGPIOE
#define KEY1_INT_EXTI_PINSOURCE 						GPIO_PinSource3
#define KEY1_INT_EXTI_LINE 									EXTI_Line3

#define KEY1_INT_EXTI_IRQ 									EXTI3_IRQn
#define KEY1_IRQChannelPreemptionPriority 	3
#define KEY1_NVIC_IRQChannelSubPriority 		3

#define KEY1_IRQHandler 										EXTI3_IRQHandler

/***************************配置KEY_0**********************************/	

#define KEY0_INT_GPIO_CLK 									(RCC_APB2Periph_GPIOE\
																						|RCC_APB2Periph_AFIO)		

#define KEY0_INT_GPIO_PORT 									GPIOE																					
#define KEY0_INT_GPIO_PIN 									GPIO_Pin_4

#define KEY0_INT_EXTI_PORTSOURCE 						GPIO_PortSourceGPIOE
#define KEY0_INT_EXTI_PINSOURCE 						GPIO_PinSource4
#define KEY0_INT_EXTI_LINE 									EXTI_Line4

#define KEY0_INT_EXTI_IRQ 									EXTI4_IRQn
#define KEY0_IRQChannelPreemptionPriority 	3
#define KEY0_NVIC_IRQChannelSubPriority 		3

#define KEY0_IRQHandler 										EXTI4_IRQHandler

/***************************KEY_0、KEY_0状态**********************************/	
#define KEY0_INT_GPIO_STAT              	GPIO_ReadInputDataBit(KEY0_INT_GPIO_PORT, KEY0_INT_GPIO_PIN)
#define KEY1_INT_GPIO_STAT              	GPIO_ReadInputDataBit(KEY1_INT_GPIO_PORT, KEY1_INT_GPIO_PIN)


void KEYEXTI_Init(void);//初始化
static void KEYEXTI_InitNVIC(void);//NVIC设置

#endif
