#pragma once

#include "RandomGenerator.h"

class LineDistributionRandomGenerator: public RandomGenerator
{
public:
	// 返回(-1.0, 1.0)之间的随机数
	double GetRandom();

protected:
	void SetSeed();
};
