#pragma once

class RandomGenerator
{
protected:
	int seed;

public:
	RandomGenerator() {};
	RandomGenerator(int seed): seed(seed) {};

	// 返回(-1.0, 1.0) 之间的随机数
	virtual double GetRandom() = 0;

protected:
	virtual void SetSeed() = 0;
};
