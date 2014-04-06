#pragma once

#include "Spirit.h"
#include "Speed.h"

class Ball: public Spirit
{
public:
	// The special ball number.
	static const int MOTHER_BALL = 0;

private:
	double radius;
	int number;

public:
	Speed speed;

public:
	Ball(double x, double y, bool visiable, double radius, int num)
	   : Spirit(x, y, visiable), radius(radius), number(num) {};
	Ball(double radius, int num): radius(radius), number(num) {};

	double GetRadius() { return radius;};
	int GetNumber() { return number;};
};
