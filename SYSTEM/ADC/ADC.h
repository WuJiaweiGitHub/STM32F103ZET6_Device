#ifndef __ADC_H
#define __ADC_H

#include <stm32f10x_conf.h>
#include <math.h>

// 转换通道个数
#define NOFCHANEL 												3

// 规则通道是否开启
//  0:     关闭
//  1:     开启
#define CHANEL_0													1
#define CHANEL_1													1
#define CHANEL_2													1
#define CHANEL_3													0
#define CHANEL_4													0
#define CHANEL_5													0
#define CHANEL_6													0
#define CHANEL_7													0
#define CHANEL_8													0
#define CHANEL_9													0
#define CHANEL_10													0
#define CHANEL_11													0
#define CHANEL_12													0
#define CHANEL_13													0
#define CHANEL_14													0
#define CHANEL_15													0

//规则通道顺序值
//范围1~16
//开启的通道其值不可重复
#define CHANEL_RANK_0											1
#define CHANEL_RANK_1											2
#define CHANEL_RANK_2											3
#define CHANEL_RANK_3											1
#define CHANEL_RANK_4											1
#define CHANEL_RANK_5											1
#define CHANEL_RANK_6											1
#define CHANEL_RANK_7											1
#define CHANEL_RANK_8											1
#define CHANEL_RANK_9											1
#define CHANEL_RANK_10										1
#define CHANEL_RANK_11										1
#define CHANEL_RANK_12										1
#define CHANEL_RANK_13										1
#define CHANEL_RANK_14										1
#define CHANEL_RANK_15									  1

#if CHANEL_0

#define ADC_CHANEL_0_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_0_PORT 								GPIOA
#define ADC_CHANEL_0_PIN 									GPIO_Pin_0

#endif /*CHANEL_0*/

#if CHANEL_1

#define ADC_CHANEL_1_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_1_PORT 								GPIOA
#define ADC_CHANEL_1_PIN 									GPIO_Pin_1

#endif /*CHANEL_1*/

#if CHANEL_2

#define ADC_CHANEL_2_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_2_PORT 								GPIOA
#define ADC_CHANEL_2_PIN 									GPIO_Pin_2

#endif /*CHANEL_2*/

#if CHANEL_3

#define ADC_CHANEL_3_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_3_PORT 								GPIOA
#define ADC_CHANEL_3_PIN 									GPIO_Pin_3

#endif /*CHANEL_3*/

#if CHANEL_4

#define ADC_CHANEL_4_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_4_PORT 								GPIOA
#define ADC_CHANEL_4_PIN 									GPIO_Pin_4

#endif /*CHANEL_4*/

#if CHANEL_5

#define ADC_CHANEL_5_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_5_PORT 								GPIOA
#define ADC_CHANEL_5_PIN 									GPIO_Pin_5

#endif /*CHANEL_5*/

#if CHANEL_6

#define ADC_CHANEL_6_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_6_PORT 								GPIOA
#define ADC_CHANEL_6_PIN 									GPIO_Pin_6

#endif /*CHANEL_6*/

#if CHANEL_7

#define ADC_CHANEL_7_GPIO_CLK 						RCC_APB2Periph_GPIOA
#define ADC_CHANEL_7_PORT 								GPIOA
#define ADC_CHANEL_7_PIN 									GPIO_Pin_7

#endif /*CHANEL_7*/

#if CHANEL_8

#define ADC_CHANEL_8_GPIO_CLK 						RCC_APB2Periph_GPIOB
#define ADC_CHANEL_8_PORT 								GPIOB
#define ADC_CHANEL_8_PIN 									GPIO_Pin_0

#endif /*CHANEL_8*/

#if CHANEL_9

#define ADC_CHANEL_9_GPIO_CLK 						RCC_APB2Periph_GPIOB
#define ADC_CHANEL_9_PORT 								GPIOB
#define ADC_CHANEL_9_PIN 									GPIO_Pin_1

#endif /*CHANEL_9*/

#if CHANEL_10

#define ADC_CHANEL_10_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_10_PORT 								GPIOC
#define ADC_CHANEL_10_PIN 								GPIO_Pin_0

#endif /*CHANEL_10*/

#if CHANEL_11

#define ADC_CHANEL_11_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_11_PORT 								GPIOC
#define ADC_CHANEL_11_PIN 								GPIO_Pin_1

#endif /*CHANEL_11*/

#if CHANEL_12

#define ADC_CHANEL_12_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_12_PORT 								GPIOC
#define ADC_CHANEL_12_PIN 								GPIO_Pin_2

#endif /*CHANEL_12*/

#if CHANEL_13

#define ADC_CHANEL_13_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_13_PORT 								GPIOC
#define ADC_CHANEL_13_PIN 								GPIO_Pin_3

#endif /*CHANEL_13*/

#if CHANEL_14

#define ADC_CHANEL_14_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_14_PORT 								GPIOC
#define ADC_CHANEL_14_PIN 								GPIO_Pin_4

#endif /*CHANEL_14*/

#if CHANEL_15

#define ADC_CHANEL_15_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_CHANEL_15_PORT 								GPIOC
#define ADC_CHANEL_15_PIN 								GPIO_Pin_5

#endif /*CHANEL_15*/

#define ADC_VOLTAGE_VALUE									3.3

// ADC 编号选择
// 可以是ADC1/2，如果使用ADC3，中断相关的宏要改成ADC3 的
#define ADC_APBxClock_FUN 								RCC_APB2PeriphClockCmd
#define ADC_x 														ADC1
#define ADC_CLK 													RCC_APB2Periph_ADC1

// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define DMA_CHANNEL 											DMA1_Channel1
#define DMA_CLOCK 												RCC_AHBPeriph_DMA1

// 外设寄存器地址
#define ADC_DR_ADDRESS 										(ADC1_BASE + 0x4C)

static void ADCx_GPIO_Config(void);
static void ADCx_Mode_Config(void);
static void ADC_DMA_Config(void);


void ADCx_Init(void);//初始化ADC 名称
double ADC_GetVal(uint8_t aisle);//参考电压值读取ADC 转换完成的数字量

#endif /*__ADC_H*/
