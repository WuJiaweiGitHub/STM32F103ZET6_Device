#include "ADC.h"

uint16_t ADC_ConvertedValue[NOFCHANEL];

static void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
	
	DMA_DeInit(DMA_CHANNEL);	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_BufferSize = NOFCHANEL;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) ADC_ConvertedValue;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) ADC_DR_ADDRESS;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA_CHANNEL, &DMA_InitStruct);
	
	DMA_Cmd(DMA_CHANNEL, ENABLE);
}

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
#if CHANEL_0
	
	RCC_APB2PeriphClockCmd(ADC_CHANEL_0_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_0_PIN;
	GPIO_Init(ADC_CHANEL_0_PORT, &GPIO_InitStruct);
	
#endif	
	
#if CHANEL_1

	RCC_APB2PeriphClockCmd(ADC_CHANEL_1_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_1_PIN;
	GPIO_Init(ADC_CHANEL_1_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_2

	RCC_APB2PeriphClockCmd(ADC_CHANEL_2_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_2_PIN;
	GPIO_Init(ADC_CHANEL_2_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_3

	RCC_APB2PeriphClockCmd(ADC_CHANEL_3_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_3_PIN;
	GPIO_Init(ADC_CHANEL_3_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_4

	RCC_APB2PeriphClockCmd(ADC_CHANEL_4_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_4_PIN;
	GPIO_Init(ADC_CHANEL_4_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_5

	RCC_APB2PeriphClockCmd(ADC_CHANEL_5_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_5_PIN;
	GPIO_Init(ADC_CHANEL_5_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_6

	RCC_APB2PeriphClockCmd(ADC_CHANEL_6_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_6_PIN;
	GPIO_Init(ADC_CHANEL_6_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_7

	RCC_APB2PeriphClockCmd(ADC_CHANEL_7_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_7_PIN;
	GPIO_Init(ADC_CHANEL_7_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_8

	RCC_APB2PeriphClockCmd(ADC_CHANEL_8_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_8_PIN;
	GPIO_Init(ADC_CHANEL_8_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_9

	RCC_APB2PeriphClockCmd(ADC_CHANEL_9_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_9_PIN;
	GPIO_Init(ADC_CHANEL_9_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_10

	RCC_APB2PeriphClockCmd(ADC_CHANEL_10_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_10_PIN;
	GPIO_Init(ADC_CHANEL_10_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_11

	RCC_APB2PeriphClockCmd(ADC_CHANEL_11_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_11_PIN;
	GPIO_Init(ADC_CHANEL_11_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_12

	RCC_APB2PeriphClockCmd(ADC_CHANEL_12_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_12_PIN;
	GPIO_Init(ADC_CHANEL_12_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_13

	RCC_APB2PeriphClockCmd(ADC_CHANEL_13_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_13_PIN;
	GPIO_Init(ADC_CHANEL_13_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_14

	RCC_APB2PeriphClockCmd(ADC_CHANEL_14_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_14_PIN;
	GPIO_Init(ADC_CHANEL_14_PORT, &GPIO_InitStruct);

#endif

#if CHANEL_15

	RCC_APB2PeriphClockCmd(ADC_CHANEL_15_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ADC_CHANEL_15_PIN;
	GPIO_Init(ADC_CHANEL_15_PORT, &GPIO_InitStruct);

#endif

}
	
static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent ;
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC_x, &ADC_InitStruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
#if CHANEL_0
	
	ADC_RegularChannelConfig(ADC_x, ADC_Channel_0, CHANEL_RANK_0, ADC_SampleTime_1Cycles5);
	
#endif	
	
#if CHANEL_1

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_1, CHANEL_RANK_1, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_2

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_2, CHANEL_RANK_2, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_3

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_3, CHANEL_RANK_3, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_4

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_4, CHANEL_RANK_4, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_5

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_5, CHANEL_RANK_5, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_6

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_6, CHANEL_RANK_6, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_7

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_7, CHANEL_RANK_7, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_8

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_8, CHANEL_RANK_8, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_9

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_9, CHANEL_RANK_9, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_10

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_10, CHANEL_RANK_10, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_11

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_11, CHANEL_RANK_11, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_12

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_12, CHANEL_RANK_12, ADC_SampleTime_1Cycles5);
	
#endif

#if CHANEL_13

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_13, CHANEL_RANK_13, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_14

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_14, CHANEL_RANK_14, ADC_SampleTime_1Cycles5);

#endif

#if CHANEL_15

	ADC_RegularChannelConfig(ADC_x, ADC_Channel_15, CHANEL_RANK_15, ADC_SampleTime_1Cycles5);

#endif
	
	ADC_DMACmd(ADC_x, ENABLE);
	
	ADC_Cmd(ADC_x, ENABLE);

 // 初始化ADC 校准寄存器
	ADC_ResetCalibration(ADC_x);
 // 等待校准寄存器初始化完成
	while (ADC_GetResetCalibrationStatus(ADC_x));

 // ADC 开始校准
	ADC_StartCalibration(ADC_x);
 // 等待校准完成
	while (ADC_GetCalibrationStatus(ADC_x));

 // 由于没有采用外部触发，所以使用软件触发ADC 转换
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);

}
	
void ADCx_Init(void)
{
	ADC_DMA_Config();
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

/**
  * @brief  能够读取 ADC 转换完成的数字量,并根据参考电压值转换为实际电压大小
  * @param  aisle:外部16通道. x (0 ~ 15) 
  * @retval None
  */
double ADC_GetVal(uint8_t aisle)
{
	return ((ADC_VOLTAGE_VALUE * ADC_ConvertedValue[aisle]) / pow(2, 12));
}
