#include "SOUND.h"

double SOUND_GetVal(void)
{
	return (ADC_GetVal(SOUND_CHANEL));
}
