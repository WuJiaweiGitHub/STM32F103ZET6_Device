#ifndef __AULTRASONIC_H
#define __AULTRASONIC_H

#include "ADC.h"

//选择量程
//1：   量程1m
//0：   量程3m
#define AULTRASONIC_RANGE_1M 								1

//ADC通道选择
#define AULTRASONIC_CHANEL									1

double AULTRASONIC_GetDistance(void);//超声波测距传感器测得实际距离

#endif /*__AULTRASONIC_H*/
