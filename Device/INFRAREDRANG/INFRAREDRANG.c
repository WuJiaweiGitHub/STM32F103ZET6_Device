#include "INFRAREDRANG.h"

const double INFRAREDRANG_a = 195.4;
const double INFRAREDRANG_b = 2.416;
const double INFRAREDRANG_c = 10.9;

double INFRAREDRANG_GetDistance(void)
{
	return (INFRAREDRANG_a * exp(-INFRAREDRANG_b * ADC_GetVal(INFRAREDRANG_CHANEL)) + INFRAREDRANG_c);
}
