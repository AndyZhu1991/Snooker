#pragma once

#include "Spirit.h"
#include "Speed.h"

class Ball: public Spirit
{
public:
	// The special ball number.
	static const int MOTHER_BALL = 0;

	static const double STD_BALL_WEIGHT;

private:
	double radius;

public:
	Speed speed;
	double weight;

public:
	Ball(double x, double y, bool visiable, double radius,
		double weight = STD_BALL_WEIGHT):
		Spirit(x, y, visiable), radius(radius), weight(weight) {};
	Ball(double radius, double weight = STD_BALL_WEIGHT)
		: radius(radius), weight(weight) {};

	double Distance(Ball& otherBall);	

	double GetRadius() { return radius;};
};
