#ifndef __RGB_H
#define __RGB_H

#include <stm32f10x_conf.h>

#if 1

#define COLOR_PWM_GPIO
/********************��ʱ��ͨ��**************************/

#define COLOR_TIM_APBxClock_FUN 		RCC_APB1PeriphClockCmd

#define COLOR_TIM_CLK 							RCC_APB1Periph_TIM4
#define COLOR_TIM_GPIO_CLK 					(RCC_APB2Periph_GPIOB)

#define COLOR_TIMx 									TIM4
#define COLOR_TIM_ARR 							256
#define COLOR_TIM_PSC 							720

/************���***************/
#define COLOR_RED_TIM_LED_PORT 							GPIOB
#define COLOR_RED_TIM_LED_PIN 							GPIO_Pin_6
#define COLOR_RED_TIM_OCxInit 							TIM_OC1Init 
#define COLOR_RED_TIM_OCxPreloadConfig 			TIM_OC1PreloadConfig
#define COLOR_RED_TIM_OCMode 								TIM_OCMode_PWM1
#define COLOR_RED_TIM_OCPolarity 						TIM_OCPolarity_Low
#define COLOR_RED_TIM_SETCOMPAREX 					TIM_SetCompare1


/************�̵�***************/
#define COLOR_GREEN_TIM_LED_PORT 							GPIOB
#define COLOR_GREEN_TIM_LED_PIN 							GPIO_Pin_7
#define COLOR_GREEN_TIM_OCxInit 							TIM_OC2Init 
#define COLOR_GREEN_TIM_OCxPreloadConfig 			TIM_OC2PreloadConfig
#define COLOR_GREEN_TIM_OCMode 								TIM_OCMode_PWM1
#define COLOR_GREEN_TIM_OCPolarity 						TIM_OCPolarity_Low
#define COLOR_GREEN_TIM_SETCOMPAREX 					TIM_SetCompare2

/************����***************/
#define COLOR_BLUE_TIM_LED_PORT 							GPIOB
#define COLOR_BLUE_TIM_LED_PIN 								GPIO_Pin_9
#define COLOR_BLUE_TIM_OCxInit 								TIM_OC4Init 
#define COLOR_BLUE_TIM_OCxPreloadConfig 			TIM_OC4PreloadConfig
#define COLOR_BLUE_TIM_OCMode 								TIM_OCMode_PWM1
#define COLOR_BLUE_TIM_OCPolarity 						TIM_OCPolarity_Low
#define COLOR_BLUE_TIM_SETCOMPAREX 						TIM_SetCompare4

#if 1

//��
#define LED_RED setCloroRGB(256,0,0)

//��
#define LED_GREEN setCloroRGB(0,256,0)

//��
#define LED_BLUE setCloroRGB(0,0,256)

//��(��+��)
#define LED_YELLOW setCloroRGB(256,256,0)

//��(��+��)
#define LED_PURPLE setCloroRGB(256,0,256)

//��(��+��)
#define LED_CYAN setCloroRGB(0,256,256)

//��(��+��+��)
#define LED_WHITE setCloroRGB(256,256,256)

//��(ȫ���ر�)
#define LED_RGBOFF setCloroRGB(0,0,0)

#endif

void RGBLED_Init(void);//RGB��ʼ��
void setCloroRGB(unsigned int red, unsigned int green, unsigned int bule);//������ʾ��ɫ��0~255��

#else

#define COLOR_GPIO

#define COLOR_TIM_GPIO_CLK 									(COLOR_RED_TIM_GPIO_CLK | \
																							COLOR_GREEN_TIM_GPIO_CLK | \
																							COLOR_BLUE_TIM_GPIO_CLK)

/************���***************/
#define COLOR_RED_TIM_LED_PORT 							GPIOB
#define COLOR_RED_TIM_LED_PIN 							GPIO_Pin_6
#define COLOR_RED_TIM_GPIO_CLK 							RCC_APB2Periph_GPIOB

/************�̵�***************/
#define COLOR_GREEN_TIM_LED_PORT 						GPIOB
#define COLOR_GREEN_TIM_LED_PIN 						GPIO_Pin_7
#define COLOR_GREEN_TIM_GPIO_CLK 						RCC_APB2Periph_GPIOB

/************����***************/
#define COLOR_BLUE_TIM_LED_PORT 						GPIOB
#define COLOR_BLUE_TIM_LED_PIN 							GPIO_Pin_9
#define COLOR_BLUE_TIM_GPIO_CLK 						RCC_APB2Periph_GPIOB

//��
#define LED_RED 														GPIO_ResetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)
								

//��
#define LED_GREEN 													GPIO_SetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��
#define LED_BLUE 														GPIO_SetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��(��+��)
#define LED_YELLOW 													GPIO_ResetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��(��+��)
#define LED_PURPLE 													GPIO_ResetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��(��+��)
#define LED_CYAN 														GPIO_SetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��(��+��+��)
#define LED_WHITE 													GPIO_ResetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_ResetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

//��(ȫ���ر�)
#define LED_RGBOFF 													GPIO_SetBits(COLOR_RED_TIM_LED_PORT, COLOR_RED_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_GREEN_TIM_LED_PORT, COLOR_GREEN_TIM_LED_PIN); \
																						GPIO_SetBits(COLOR_BLUE_TIM_LED_PORT, COLOR_BLUE_TIM_LED_PIN)

void RGBLED_Init(void);//RGB��ʼ��

#endif
#endif
