#ifndef __KEYPAD_H
#define __KEYPAD_H

#include <stm32f10x_conf.h>

//��ʱ����
extern void delay_ms(u16 nms);

//***************��һ��********************/
#define KEY_C1_PORT 							GPIOG
#define KEY_C1_PIN 								GPIO_Pin_8
#define KEY_C1_TIM_GPIO_CLK				RCC_APB2Periph_GPIOG

//***************�ڶ���********************/
#define KEY_C2_PORT 							GPIOC
#define KEY_C2_PIN 								GPIO_Pin_7
#define KEY_C2_TIM_GPIO_CLK				RCC_APB2Periph_GPIOC

//***************������********************/
#define KEY_C3_PORT 							GPIOC
#define KEY_C3_PIN 								GPIO_Pin_9
#define KEY_C3_TIM_GPIO_CLK				RCC_APB2Periph_GPIOC

//***************������********************/
#define KEY_C4_PORT 							GPIOA
#define KEY_C4_PIN 								GPIO_Pin_13
#define KEY_C4_TIM_GPIO_CLK				RCC_APB2Periph_GPIOA

//***************��һ��********************/
#define KEY_R1_PORT 							GPIOG
#define KEY_R1_PIN 								GPIO_Pin_6
#define KEY_R1_TIM_GPIO_CLK				RCC_APB2Periph_GPIOG

//***************�ڶ���********************/
#define KEY_R2_PORT 							GPIOG
#define KEY_R2_PIN 								GPIO_Pin_4
#define KEY_R2_TIM_GPIO_CLK				RCC_APB2Periph_GPIOG

//***************������********************/
#define KEY_R3_PORT 							GPIOG
#define KEY_R3_PIN 								GPIO_Pin_2
#define KEY_R3_TIM_GPIO_CLK				RCC_APB2Periph_GPIOG
	
//***************������********************/
#define KEY_R4_PORT 							GPIOD
#define KEY_R4_PIN 								GPIO_Pin_12
#define KEY_R4_TIM_GPIO_CLK				RCC_APB2Periph_GPIOD


//***************��������Ķ�********************/
#define KEY_TIM_GPIO_CLK 					(KEY_C1_TIM_GPIO_CLK | \
																		KEY_C2_TIM_GPIO_CLK | \
																		KEY_C3_TIM_GPIO_CLK | \
																		KEY_C4_TIM_GPIO_CLK | \
																		KEY_R1_TIM_GPIO_CLK | \
																		KEY_R2_TIM_GPIO_CLK | \
																		KEY_R3_TIM_GPIO_CLK | \
																		KEY_R4_TIM_GPIO_CLK)

//***************������1********************/
#define SET_BIT_C0_4							GPIO_SetBits(KEY_C1_PORT, KEY_C1_PIN);\
																	GPIO_SetBits(KEY_C2_PORT, KEY_C2_PIN);\
																	GPIO_SetBits(KEY_C3_PORT, KEY_C3_PIN);\
																	GPIO_SetBits(KEY_C4_PORT, KEY_C4_PIN)

//***************����һ��********************/
#define CHECK_C1 									GPIO_SetBits(KEY_C1_PORT, KEY_C1_PIN);\
																	GPIO_ResetBits(KEY_C2_PORT, KEY_C2_PIN);\
																	GPIO_ResetBits(KEY_C3_PORT, KEY_C3_PIN);\
																	GPIO_ResetBits(KEY_C4_PORT, KEY_C4_PIN)

//***************���ڶ���********************/
#define CHECK_C2									GPIO_ResetBits(KEY_C1_PORT, KEY_C1_PIN);\
																	GPIO_SetBits(KEY_C2_PORT, KEY_C2_PIN);\
																	GPIO_ResetBits(KEY_C3_PORT, KEY_C3_PIN);\
																	GPIO_ResetBits(KEY_C4_PORT, KEY_C4_PIN)

//***************��������********************/
#define CHECK_C3									GPIO_ResetBits(KEY_C1_PORT, KEY_C1_PIN);\
																	GPIO_ResetBits(KEY_C2_PORT, KEY_C2_PIN);\
																	GPIO_SetBits(KEY_C3_PORT, KEY_C3_PIN);\
																	GPIO_ResetBits(KEY_C4_PORT, KEY_C4_PIN)

//***************��������********************/
#define CHECK_C4									GPIO_ResetBits(KEY_C1_PORT, KEY_C1_PIN);\
																	GPIO_ResetBits(KEY_C2_PORT, KEY_C2_PIN);\
																	GPIO_ResetBits(KEY_C3_PORT, KEY_C3_PIN);\
																	GPIO_SetBits(KEY_C4_PORT, KEY_C4_PIN);															

//***************����״̬********************/
#define CHECK_R_STATIC						(GPIO_ReadInputDataBit(KEY_R1_PORT, KEY_R1_PIN) ||\
																	GPIO_ReadInputDataBit(KEY_R2_PORT, KEY_R2_PIN) || \
																	GPIO_ReadInputDataBit(KEY_R3_PORT, KEY_R3_PIN) || \
																	GPIO_ReadInputDataBit(KEY_R4_PORT, KEY_R4_PIN))

//***************����״̬********************/
#define R1_STATIC 								GPIO_ReadInputDataBit(KEY_R1_PORT, KEY_R1_PIN)
#define R2_STATIC 								GPIO_ReadInputDataBit(KEY_R2_PORT, KEY_R2_PIN)
#define R3_STATIC 								GPIO_ReadInputDataBit(KEY_R3_PORT, KEY_R3_PIN)
#define R4_STATIC 								GPIO_ReadInputDataBit(KEY_R4_PORT, KEY_R4_PIN)														

#define NO_KET_DOWN 							0
#define KEY1_DOWN 								1
#define KEY2_DOWN 								2
#define KEY3_DOWN 								3
#define KEY4_DOWN 								4
#define KEY5_DOWN 								5
#define KEY6_DOWN 								6
#define KEY7_DOWN 								7
#define KEY8_DOWN 								8
#define KEY9_DOWN 								9
#define KEY10_DOWN 								10
#define KEY11_DOWN 								11
#define KEY12_DOWN 								12
#define KEY13_DOWN 								13
#define KEY14_DOWN 								14
#define KEY15_DOWN 								15
#define KEY16_DOWN 								16

void KeyPad_Init(void);//������ʼ��
unsigned char KeyPad_Check(void);//�������

#endif
