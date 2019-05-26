#include "i2c_ee.h"

static void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能与 GPIO 有关的时钟 */
	EEPROM_I2C_GPIO_APBxClock_FUN ( EEPROM_I2C_GPIO_CLK, ENABLE );

	/* I2C_SCL、 I2C_SDA*/
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // 开漏输出
	GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // 开漏输出
	GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);
}

static void I2C_Mode_Configu(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	
	EEPROM_I2C_APBxClock_FUN ( EEPROM_I2C_CLK, ENABLE);
	
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = I2C_Speed;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = I2Cx_OWN_ADDRESS7;
	I2C_Init(I2C1, &I2C_InitStruct);
	
	I2C_Cmd(I2C1, ENABLE);
}

void I2C_EE_Init(void)
{
	I2C_GPIO_Config();
	I2C_Mode_Configu();
}

/**
 * @brief I2C 等待事件超时的情况下会调用这个函数来处理
 * @param errorCode：错误代码，可以用来定位是哪个环节出错.
 * @retval 返回 0，表示 IIC 读取失败.
 */
static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
	/* 使用串口 printf 输出错误信息，方便调试 */
	printf("I2C 等待超时!errorCode = %d\r\n",errorCode);
	return 0;
}

/**
* @brief 写一个字节到 I2C EEPROM 中
 * @param pBuffer:缓冲区指针
 * @param WriteAddr:写地址
 * @retval 正常返回 1，异常返回 0
 */
unsigned short I2CTimeout = 0;

static uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr)
{
	I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(SUCCESS == I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT ))
	{
		if(0 == (--I2CTimeout))
		{
			return I2C_TIMEOUT_UserCallback(0);
			I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
		}
	}
	
	I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(SUCCESS == I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if(0 == (--I2CTimeout))
		{
			return I2C_TIMEOUT_UserCallback(1);
		}
	}	
	
	I2C_SendData(EEPROM_I2Cx, WriteAddr);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(SUCCESS == I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
	{
		if(0 == (--I2CTimeout))
		{
			return I2C_TIMEOUT_UserCallback(2);
		}
	}	
	
	I2C_SendData(EEPROM_I2Cx, *pBuffer);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(SUCCESS == I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
	{
		if(0 == (--I2CTimeout))
		{
			return I2C_TIMEOUT_UserCallback(3);
		}
	}
		
	I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
	
	return 1;

}

/**
 * @brief 等待 EEPROM 到准备状态
 * @param 无
 * @retval 无
 *Once the internally timed write cycle has started and the
 *EEPROM inputs are disabled, acknowledge polling can be initiated. This involves send-
 *ing a start condition followed by the device address word. The read/write bit is
 *representative of the operation desired. Only if the internal write cycle has completed
 *will the EEPROM respond with a “0”, allowing the read or write sequence to continue.
 */
void I2C_EE_WaitEepromStandbyState(void)
{
	uint16_t status = 0;
	/*若EEPROM 接收到地址后返回应答信号，则表示 EEPROM 已经准备好*/
	do
	{
		I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
		
		status = I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1);
		
		I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	} while(!(status & 0x0002));
	
	/*函数中检测响应是通过读取 STM32 的 SR1 寄存器的 ADDR 位及 AF 位来实现的，当
		I2C 设备响应了地址的时候， ADDR 会置 1，若应答失败， AF 位会置 1*/
	
	I2C_ClearFlag(EEPROM_I2Cx, I2C_FLAG_AF);
	
	I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
}

/**
 * @brief 将缓冲区中的数据写到 I2C EEPROM 中，采用单字节写入的方式，
 速度比页写入慢
 * @param pBuffer:缓冲区指针
 * @param WriteAddr:写地址
 * @param NumByteToWrite:写的字节数
 * @retval 无
 */
static uint8_t I2C_EE_ByetsWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t i = 0;
	uint8_t res = 0;
	
	for(i = 0; i < NumByteToWrite; i++)
	{
		I2C_EE_WaitEepromStandbyState();//等待EEPROM准备完毕
		res += I2C_EE_ByteWrite(pBuffer + i, WriteAddr + i);
	}
	
	return res;
}

/**
 * @brief 在 EEPROM 的一个写循环中可以写多个字节，但一次写入的字节数
 * 不能超过 EEPROM 页的大小， AT24C02 每页有 8 个字节
 * @param
 * @param pBuffer:缓冲区指针
 * @param WriteAddr:写地址,地址必须要与8地址对其
 * @param NumByteToWrite:要写的字节数要求 NumByToWrite 小于页大小
 * @retval 正常返回 1，异常返回 0
 */
static uint8_t I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{
	I2CTimeout = I2CT_LONG_TIMEOUT;

  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))   
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
  } 
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) 
		{
			I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
			
			return I2C_TIMEOUT_UserCallback(5);
		}
  } 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(6);
		}
  } 
  
  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(EEPROM_I2Cx, WriteAddr);  

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(7);
		}
  } 

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(EEPROM_I2Cx, *pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if((I2CTimeout--) == 0) 
			{
				return I2C_TIMEOUT_UserCallback(8);
			}
    } 
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
  
  return 1;
}

 /**
 * @brief 将缓冲区中的数据写到 I2C EEPROM 中
 * @param
 * @arg pBuffer:缓冲区指针
 * @arg WriteAddr:写地址
 * @arg NumByteToWrite:写的字节数
 * @retval 无
 */
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
	unsigned char NumOfPage = 0;
	unsigned char NumOfSingle=0;
	unsigned char Addr = 0;
	unsigned char count = 0;
	unsigned char temp = 0;

	/*mod 运算求余，计算是否在页开头*/
	Addr = WriteAddr % I2C_PageSize;

	/*在该页的字节数*/
	count = I2C_PageSize - Addr;

	/*计算出要写多少整数页*/
	NumOfPage = NumByteToWrite / I2C_PageSize;

	/*mod 运算求余，计算出剩余不满一页的字节数*/
	NumOfSingle = NumByteToWrite % I2C_PageSize;
	
	if(0 == Addr)//表明在页的开头处
	{
		if(0 == NumOfPage)//表明数据没有一页
		{
			I2C_EE_ByetsWrite(pBuffer, WriteAddr, NumByteToWrite);
			I2C_EE_WaitEepromStandbyState();
		}else//表明数据分布在多页内
		{
			while(NumOfPage--)
			{
				I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
				I2C_EE_WaitEepromStandbyState();
				pBuffer += I2C_PageSize;
				WriteAddr += I2C_PageSize;
			}
			
			if(0 != NumOfSingle)
			{
				//I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_ByetsWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_WaitEepromStandbyState();
			}	
		}
	}else//表明首地址不为8的倍数
	{
		if(0 == NumOfSingle)//表明数据没有一页
		{
			if(count < NumOfSingle)//数据项没有一页，但在两页里
			{
				temp = NumOfSingle - count;
				
				//I2C_EE_PageWrite(pBuffer, WriteAddr, count);
				I2C_EE_ByetsWrite(pBuffer, WriteAddr, count);
				I2C_EE_WaitEepromStandbyState();
				
				pBuffer += count;
				WriteAddr += count;
				
				I2C_EE_PageWrite(pBuffer, WriteAddr, temp);
				I2C_EE_WaitEepromStandbyState();
			}else//一页
			{
				I2C_EE_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
				I2C_EE_WaitEepromStandbyState();
			}
			
		}else//多页
		{
			//I2C_EE_PageWrite(pBuffer, WriteAddr, count);
			I2C_EE_ByetsWrite(pBuffer, WriteAddr, count);
			I2C_EE_WaitEepromStandbyState();
		
			pBuffer += count;
			WriteAddr += count;
			
			while(NumOfPage--)
			{
				I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
				I2C_EE_WaitEepromStandbyState();
				pBuffer += I2C_PageSize;
				WriteAddr += I2C_PageSize;
			}
			
			if(0 != NumOfSingle)
			{
				//I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_ByetsWrite(pBuffer, WriteAddr, count);
				I2C_EE_WaitEepromStandbyState();
			}	
		}
	}
}

/**
 * @brief 从 EEPROM 里面读取一块数据
 * @param pBuffer:存放从 EEPROM 读取的数据的缓冲区指针
 * @param ReadAddr:接收数据的 EEPROM 的地址
 * @param NumByteToRead:要从 EEPROM 读取的字节数
 * @retval 正常返回 1，异常返回 0
 */
uint8_t I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, u16 NumByteToRead)
{
	I2CTimeout = I2CT_LONG_TIMEOUT;

  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))   
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(9);
		}
  } 
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0)
		{
			I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
			
			return I2C_TIMEOUT_UserCallback(10);
		}			
  } 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(11);
		}
  } 
  
  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(EEPROM_I2Cx, ReadAddr);  

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(12);
		}
  } 
	
//	I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
//	
//	I2CTimeout = I2CT_LONG_TIMEOUT;

//  while(I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))   
//  {
//    if((I2CTimeout--) == 0) 
//		{
//			return I2C_TIMEOUT_UserCallback(13);
//		}
//  } 
  
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) 
		{
			I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
			
			return I2C_TIMEOUT_UserCallback(14);
		}
  } 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Receiver);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))  
  {
    if((I2CTimeout--) == 0) 
		{
			return I2C_TIMEOUT_UserCallback(15);
		}
  } 
	
	while(NumByteToRead)
	{
		if(1 == NumByteToRead)
		{
			I2C_AcknowledgeConfig(EEPROM_I2Cx, DISABLE);
			
			I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
		}
		
		I2CTimeout = I2CT_FLAG_TIMEOUT;
		/* Test on EV6 and clear it */
		while(!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  
		{
			if((I2CTimeout--) == 0) 
			{
				return I2C_TIMEOUT_UserCallback(16);
			}
		} 
		
		*pBuffer = I2C_ReceiveData(EEPROM_I2Cx);
		
		pBuffer++;
		NumByteToRead--;
	}
	
	I2C_AcknowledgeConfig(EEPROM_I2Cx, ENABLE);
	
	return 1;
}
