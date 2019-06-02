#ifndef __INFRAREDRANG_H
#define __INFRAREDRANG_H

#include "ADC.h"

//通道选择
#define INFRAREDRANG_CHANEL										0

extern const double INFRAREDRANG_a;
extern const double INFRAREDRANG_b;
extern const double INFRAREDRANG_c;

double INFRAREDRANG_GetDistance(void);//红外测距传感器测得实际距离

#endif /*__INFRAREDRANG_H*/
