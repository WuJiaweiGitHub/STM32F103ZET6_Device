#include "KeyPad.h"

void KeyPad_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY_TIM_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = KEY_C1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_C1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_C2_PIN;
	GPIO_Init(KEY_C2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_C3_PIN;
	GPIO_Init(KEY_C3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_C4_PIN;
	GPIO_Init(KEY_C4_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_R1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY_R1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_R2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY_R2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_R3_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY_R3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = KEY_R4_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY_R4_PORT, &GPIO_InitStruct);
}
	
unsigned char KeyPad_Check(void)
{
	unsigned char keyValue = 0;
	unsigned char column = 0;
	
	SET_BIT_C0_4;
	if(1 == CHECK_R_STATIC)
	{
		delay_ms(10);
		if(1 == CHECK_R_STATIC)
		{
			CHECK_C1;
			if(1 == CHECK_R_STATIC)
			{
				column = (column | R1_STATIC) << 1;
				column = (column | R2_STATIC) << 1;
				column = (column | R3_STATIC) << 1;
				column = (column | R4_STATIC);
				
				switch(column & 0x0F)
				{
					case 0x8:
						keyValue = KEY1_DOWN; break;
					case 0x4:
						keyValue = KEY5_DOWN; break;
					case 0x2:
						keyValue = KEY9_DOWN; break;
					case 0x1:
						keyValue = KEY13_DOWN; break;
					default:
						keyValue = NO_KET_DOWN; break;
				}
				
			}
			
			CHECK_C2;
			if(1 == CHECK_R_STATIC)
			{
				column = (column | R1_STATIC) << 1;
				column = (column | R2_STATIC) << 1;
				column = (column | R3_STATIC) << 1;
				column = (column | R4_STATIC);
				
				switch(column & 0x0F)
				{
					case 0x8:
						keyValue = KEY2_DOWN; break;
					case 0x4:
						keyValue = KEY6_DOWN; break;
					case 0x2:
						keyValue = KEY10_DOWN; break;
					case 0x1:
						keyValue = KEY14_DOWN; break;
					default:
						keyValue = NO_KET_DOWN; break;
				}
			}
			
			CHECK_C3;
			if(1 == CHECK_R_STATIC)
			{
				column = (column | R1_STATIC) << 1;
				column = (column | R2_STATIC) << 1;
				column = (column | R3_STATIC) << 1;
				column = (column | R4_STATIC);
				
				switch(column & 0x0F)
				{
					case 0x8:
						keyValue = KEY3_DOWN; break;
					case 0x4:
						keyValue = KEY7_DOWN; break;
					case 0x2:
						keyValue = KEY11_DOWN; break;
					case 0x1:
						keyValue = KEY15_DOWN; break;
					default:
						keyValue = NO_KET_DOWN; break;
				}
			}
			
			CHECK_C4;
			if(1 == CHECK_R_STATIC)
			{
				column = (column | R1_STATIC) << 1;
				column = (column | R2_STATIC) << 1;
				column = (column | R3_STATIC) << 1;
				column = (column | R4_STATIC);
				
				switch(column & 0x0F)
				{
					case 0x8:
						keyValue = KEY4_DOWN; break;
					case 0x4:
						keyValue = KEY8_DOWN; break;
					case 0x2:
						keyValue = KEY12_DOWN; break;
					case 0x1:
						keyValue = KEY16_DOWN; break;
					default:
						keyValue = NO_KET_DOWN; break;
				}
			}
			
			while(1 == CHECK_R_STATIC)
			{
				
			}
				
		}	

	}
	
	return keyValue;
}

