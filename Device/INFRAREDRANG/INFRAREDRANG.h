#ifndef __INFRAREDRANG_H
#define __INFRAREDRANG_H

#include "ADC.h"

//ͨ��ѡ��
#define INFRAREDRANG_CHANEL										0

extern const double INFRAREDRANG_a;
extern const double INFRAREDRANG_b;
extern const double INFRAREDRANG_c;

double INFRAREDRANG_GetDistance(void);//�����ഫ�������ʵ�ʾ���

#endif /*__INFRAREDRANG_H*/
