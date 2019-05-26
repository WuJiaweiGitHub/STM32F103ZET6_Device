#ifndef __USART_H
#define __USART_H

#include <stm32f10x_conf.h>
#include <stdio.h>

#define DEBUG_USART1 1
#define DEBUG_USART2 0
#define DEBUG_USART3 0
#define DEBUG_USART4 0
#define DEBUG_USART5 0


#if DEBUG_USART1
//串口宏定义，不同的串口挂载的总线和 IO 不一样，移植时需要修改这几个宏
//串口 1-USART1
#define DEBUG_USARTx 										USART1
#define DEBUG_USART_CLK 								RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd 					RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE 						115200

//抢占优先级
#define DEBUG_USART_NVIC_PRE 						0
//比较优先级
#define DEBUG_USART_NVIC_SUB 						0

// USART GPIO 引脚宏定义
#define DEBUG_USART_GPIO_CLK 						(RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd 		RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT 				GPIOA
#define DEBUG_USART_TX_GPIO_PIN 				GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT 				GPIOA
#define DEBUG_USART_RX_GPIO_PIN 				GPIO_Pin_10

#define DEBUG_USART_IRQ 								USART1_IRQn
#define DEBUG_USART_IRQHandler 					USART1_IRQHandler
#elif DEBUG_USART2
//串口宏定义，不同的串口挂载的总线和 IO 不一样，移植时需要修改这几个宏
//串口2-USART2

#define  DEBUG_USARTx                   USART2
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

//抢占优先级
#define DEBUG_USART_NVIC_PRE 						0
//比较优先级
#define DEBUG_USART_NVIC_SUB 						0

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG_USART_IRQ                USART2_IRQn
#define  DEBUG_USART_IRQHandler         USART2_IRQHandler

#elif DEBUG_USART3
//串口宏定义，不同的串口挂载的总线和 IO 不一样，移植时需要修改这几个宏
// 串口3-USART3
#define  DEBUG_USARTx                   USART3
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART3
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

//抢占优先级
#define DEBUG_USART_NVIC_PRE 0
//比较优先级
#define DEBUG_USART_NVIC_SUB 0

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOB
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                USART3_IRQn
#define  DEBUG_USART_IRQHandler         USART3_IRQHandler

#elif DEBUG_USART4
//串口宏定义，不同的串口挂载的总线和 IO 不一样，移植时需要修改这几个宏
// 串口4-UART4
#define  DEBUG_USARTx                   UART4
#define  DEBUG_USART_CLK                RCC_APB1Periph_UART4
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

//抢占优先级
#define DEBUG_USART_NVIC_PRE 						0
//比较优先级
#define DEBUG_USART_NVIC_SUB 						0

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOC
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                UART4_IRQn
#define  DEBUG_USART_IRQHandler         UART4_IRQHandler

#elif DEBUG_USART5
//串口宏定义，不同的串口挂载的总线和 IO 不一样，移植时需要修改这几个宏
// 串口5-UART5
#define  DEBUG_USARTx                   UART5
#define  DEBUG_USART_CLK                RCC_APB1Periph_UART5
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

//抢占优先级
#define DEBUG_USART_NVIC_PRE 						0
//比较优先级
#define DEBUG_USART_NVIC_SUB 						0

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_12
#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_2

#define  DEBUG_USART_IRQ                UART5_IRQn
#define  DEBUG_USART_IRQHandler         UART5_IRQHandler

#endif

void usartInit( void );
static void NVIC_Configuration(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif
