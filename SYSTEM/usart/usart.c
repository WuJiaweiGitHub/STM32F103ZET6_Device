#include "usart.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USARTx->SR&0X40)==0);//循环发送,直到发送完毕   
    DEBUG_USARTx->DR = (u8) ch;      
	return ch;
}
#else

/*使用microLib的方法*/
//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/*error*/
//int fputc(int ch, FILE *f)
//{
//	USART1->SR;//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
//	USART_SendData(DEBUG_USARTx, (uint8_t) ch);

//	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TC) == RESET) {}	
//   
//    return ch;
//}
#endif

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = DEBUG_USART_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = DEBUG_USART_NVIC_PRE;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = DEBUG_USART_NVIC_SUB;
	NVIC_Init(&NVIC_InitStruct);
}

void usartInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	
	USART_DeInit(DEBUG_USARTx);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(DEBUG_USARTx, &USART_InitStruct);
	
	NVIC_Configuration();
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

/***************** 发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到 USART */
	USART_SendData(pUSARTx,ch);
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/***************** 发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do {
		Usart_SendByte( pUSARTx, *(str + k) );
		k++;
	} while (*(str + k)!='\0');
	
	/* 等待发送完成 */
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) 
	{
		
	}
	
}

void DEBUG_USART_IRQHandler(void)
{
	uint8_t ucTemp;
	
	if (USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!= RESET)
	{
		USART_ClearITPendingBit(DEBUG_USARTx, USART_IT_RXNE);
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
		USART_SendData(DEBUG_USARTx,ucTemp);
	}

}
