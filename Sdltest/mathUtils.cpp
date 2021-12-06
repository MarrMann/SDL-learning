#include "mathUtils.h"

uint8_t MathUtils::Rand()
{
	return rand();
}

uint8_t MathUtils::Rand(int range)
{
	return rand() % range;
}