#include "i2c_ee.h"

static void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ���� GPIO �йص�ʱ�� */
	EEPROM_I2C_GPIO_APBxClock_FUN ( EEPROM_I2C_GPIO_CLK, ENABLE );

	/* I2C_SCL�� I2C_SDA*/
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // ��©���
	GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // ��©���
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
 * @brief I2C �ȴ��¼���ʱ������»�����������������
 * @param errorCode��������룬����������λ���ĸ����ڳ���.
 * @retval ���� 0����ʾ IIC ��ȡʧ��.
 */
static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
	/* ʹ�ô��� printf ���������Ϣ��������� */
	printf("I2C �ȴ���ʱ!errorCode = %d\r\n",errorCode);
	return 0;
}

/**
* @brief дһ���ֽڵ� I2C EEPROM ��
 * @param pBuffer:������ָ��
 * @param WriteAddr:д��ַ
 * @retval �������� 1���쳣���� 0
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
 * @brief �ȴ� EEPROM ��׼��״̬
 * @param ��
 * @retval ��
 *Once the internally timed write cycle has started and the
 *EEPROM inputs are disabled, acknowledge polling can be initiated. This involves send-
 *ing a start condition followed by the device address word. The read/write bit is
 *representative of the operation desired. Only if the internal write cycle has completed
 *will the EEPROM respond with a ��0��, allowing the read or write sequence to continue.
 */
void I2C_EE_WaitEepromStandbyState(void)
{
	uint16_t status = 0;
	/*��EEPROM ���յ���ַ�󷵻�Ӧ���źţ����ʾ EEPROM �Ѿ�׼����*/
	do
	{
		I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);
		
		status = I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1);
		
		I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	} while(!(status & 0x0002));
	
	/*�����м����Ӧ��ͨ����ȡ STM32 �� SR1 �Ĵ����� ADDR λ�� AF λ��ʵ�ֵģ���
		I2C �豸��Ӧ�˵�ַ��ʱ�� ADDR ���� 1����Ӧ��ʧ�ܣ� AF λ���� 1*/
	
	I2C_ClearFlag(EEPROM_I2Cx, I2C_FLAG_AF);
	
	I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
}

/**
 * @brief ���������е�����д�� I2C EEPROM �У����õ��ֽ�д��ķ�ʽ��
 �ٶȱ�ҳд����
 * @param pBuffer:������ָ��
 * @param WriteAddr:д��ַ
 * @param NumByteToWrite:д���ֽ���
 * @retval ��
 */
static uint8_t I2C_EE_ByetsWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t i = 0;
	uint8_t res = 0;
	
	for(i = 0; i < NumByteToWrite; i++)
	{
		I2C_EE_WaitEepromStandbyState();//�ȴ�EEPROM׼�����
		res += I2C_EE_ByteWrite(pBuffer + i, WriteAddr + i);
	}
	
	return res;
}

/**
 * @brief �� EEPROM ��һ��дѭ���п���д����ֽڣ���һ��д����ֽ���
 * ���ܳ��� EEPROM ҳ�Ĵ�С�� AT24C02 ÿҳ�� 8 ���ֽ�
 * @param
 * @param pBuffer:������ָ��
 * @param WriteAddr:д��ַ,��ַ����Ҫ��8��ַ����
 * @param NumByteToWrite:Ҫд���ֽ���Ҫ�� NumByToWrite С��ҳ��С
 * @retval �������� 1���쳣���� 0
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
 * @brief ���������е�����д�� I2C EEPROM ��
 * @param
 * @arg pBuffer:������ָ��
 * @arg WriteAddr:д��ַ
 * @arg NumByteToWrite:д���ֽ���
 * @retval ��
 */
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
	unsigned char NumOfPage = 0;
	unsigned char NumOfSingle=0;
	unsigned char Addr = 0;
	unsigned char count = 0;
	unsigned char temp = 0;

	/*mod �������࣬�����Ƿ���ҳ��ͷ*/
	Addr = WriteAddr % I2C_PageSize;

	/*�ڸ�ҳ���ֽ���*/
	count = I2C_PageSize - Addr;

	/*�����Ҫд��������ҳ*/
	NumOfPage = NumByteToWrite / I2C_PageSize;

	/*mod �������࣬�����ʣ�಻��һҳ���ֽ���*/
	NumOfSingle = NumByteToWrite % I2C_PageSize;
	
	if(0 == Addr)//������ҳ�Ŀ�ͷ��
	{
		if(0 == NumOfPage)//��������û��һҳ
		{
			I2C_EE_ByetsWrite(pBuffer, WriteAddr, NumByteToWrite);
			I2C_EE_WaitEepromStandbyState();
		}else//�������ݷֲ��ڶ�ҳ��
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
	}else//�����׵�ַ��Ϊ8�ı���
	{
		if(0 == NumOfSingle)//��������û��һҳ
		{
			if(count < NumOfSingle)//������û��һҳ��������ҳ��
			{
				temp = NumOfSingle - count;
				
				//I2C_EE_PageWrite(pBuffer, WriteAddr, count);
				I2C_EE_ByetsWrite(pBuffer, WriteAddr, count);
				I2C_EE_WaitEepromStandbyState();
				
				pBuffer += count;
				WriteAddr += count;
				
				I2C_EE_PageWrite(pBuffer, WriteAddr, temp);
				I2C_EE_WaitEepromStandbyState();
			}else//һҳ
			{
				I2C_EE_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
				I2C_EE_WaitEepromStandbyState();
			}
			
		}else//��ҳ
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
 * @brief �� EEPROM �����ȡһ������
 * @param pBuffer:��Ŵ� EEPROM ��ȡ�����ݵĻ�����ָ��
 * @param ReadAddr:�������ݵ� EEPROM �ĵ�ַ
 * @param NumByteToRead:Ҫ�� EEPROM ��ȡ���ֽ���
 * @retval �������� 1���쳣���� 0
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
