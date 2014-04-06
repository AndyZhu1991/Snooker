#include "stdafx.h"
#include "LineDistributionRandomGenerator.h"
#include <stdlib.h>
#include <time.h>

void LineDistributionRandomGenerator::SetSeed()
{
	srand(seed);
}

double LineDistributionRandomGenerator::GetRandom()
{
	return rand() * 2.0 / RAND_MAX - 1.0;
}
