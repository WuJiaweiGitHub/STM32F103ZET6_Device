#include "AULTRASONIC.h"

double AULTRASONIC_GetDistance(void)
{
#if AULTRASONIC_RANGE_1M
	return (ADC_GetVal(AULTRASONIC_CHANEL) * (1024 / 5));
#else
	return (ADC_GetVal(AULTRASONIC_CHANEL) * (3072 / 5));
#endif
	
}
