#include "usart_dma.h"

unsigned char Rxdata[256];

unsigned char temp[12] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
//unsigned char *temp = "hello world!!!\n";

void USARTx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = 256;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = ( uint32_t ) Rxdata;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	//DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_BASE + 0x04;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
	
	DMA_Cmd(DMA1_Channel4, ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = 256;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_MemoryBaseAddr = ( uint32_t ) Rxdata;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_BASE + 0x04;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	DMA_Init(DMA1_Channel5, &DMA_InitStruct);
	
	DMA_Cmd(DMA1_Channel5, ENABLE);
}
