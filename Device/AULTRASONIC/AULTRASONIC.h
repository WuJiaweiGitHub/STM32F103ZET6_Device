#ifndef __AULTRASONIC_H
#define __AULTRASONIC_H

#include "ADC.h"

//ѡ������
//1��   ����1m
//0��   ����3m
#define AULTRASONIC_RANGE_1M 								1

//ADCͨ��ѡ��
#define AULTRASONIC_CHANEL									1

double AULTRASONIC_GetDistance(void);//��������ഫ�������ʵ�ʾ���

#endif /*__AULTRASONIC_H*/
