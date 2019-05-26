#ifndef __I2C_EE_H
#define __I2C_EE_H

#include <stm32f10x_conf.h>

#include "usart.h"

 /**************************I2C �������壬 I2C1 �� I2C2*********************/
#define EEPROM_I2Cx 											I2C1
#define EEPROM_I2C_APBxClock_FUN 					RCC_APB1PeriphClockCmd
#define EEPROM_I2C_CLK 										RCC_APB1Periph_I2C1
#define EEPROM_I2C_GPIO_APBxClock_FUN 		RCC_APB2PeriphClockCmd
#define EEPROM_I2C_GPIO_CLK 							RCC_APB2Periph_GPIOB
#define EEPROM_I2C_SCL_PORT	 							GPIOB
#define EEPROM_I2C_SCL_PIN 								GPIO_Pin_6
#define EEPROM_I2C_SDA_PORT 							GPIOB
#define EEPROM_I2C_SDA_PIN 								GPIO_Pin_7



/* STM32 I2C ����ģʽ */
#define I2C_Speed 400000 //*

/* �����ַֻҪ�� STM32 ��ҵ� I2C ������ַ��һ������ */
#define I2Cx_OWN_ADDRESS7 0X0A

/* AT24C01/02 ÿҳ�� 8 ���ֽ� */
#define I2C_PageSize 8

/* 
 * AT24C02 2kb = 2048bit = 2048/8 B = 256 B
 * 32 pages of 8 bytes each
 *
 * Device Address
 * 1	R
 * 0	W
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */

/***************************************************************/
/*ͨѶ�ȴ���ʱʱ��*/
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);

static void I2C_GPIO_Config(void);
static void I2C_Mode_Configu(void);

void I2C_EE_WaitEepromStandbyState(void);//�ȴ� EEPROM ��׼��״̬

void I2C_EE_Init(void);//��ʼ��

static uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr);//�ֽ�д��
static uint8_t I2C_EE_ByetsWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);//����ֽ�д��
static uint8_t I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite);//ҳд��,�׵�ַΪ8�ı���

void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);//д��
uint8_t I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, u16 NumByteToRead);//��ȡ����
#endif    /*__I2C_EE_H*/
