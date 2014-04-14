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
	int number;

public:
	Speed speed;
	double weight;

public:
	Ball(double x, double y, bool visiable, double radius, int num,
		double weight): Spirit(x, y, visiable),
		radius(radius), number(num), weight(STD_BALL_WEIGHT) {};
	Ball(double radius, int num, double weight)
		: radius(radius), number(num), weight(STD_BALL_WEIGHT) {};

	double Distance(Ball& otherBall);	

	double GetRadius() { return radius;};
	int GetNumber() { return number;};
};
