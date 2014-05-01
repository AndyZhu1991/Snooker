#pragma once

#include "Spirit.h"
#include "Speed.h"

class Ball: public Spirit
{
public:
	// The ball type.
	static const int MOTHER_BALL = 0;
	static const int RED_BALL = 1;
	static const int YELLOW_BALL = 2;
	static const int GREEN_BALL = 3;
	static const int BROWN_BALL = 4;
	static const int BLUE_BALL = 5;
	static const int PINK_BALL = 6;
	static const int BLACK_BALL = 7;

	// Some standard attributes of ball
	static const double STD_WEIGHT;
	static const double STD_RADIUS;

private:
	double radius;
	int type;

public:
	Speed speed;
	double weight;

public:
	Ball(double x, double y, bool visiable, double radius = STD_RADIUS,
		double weight = STD_WEIGHT):
		Spirit(x, y, visiable), radius(radius), weight(weight) {};
		Ball(double radius = STD_RADIUS, double weight = STD_WEIGHT)
		: radius(radius), weight(weight) {};

	double Distance(Ball& otherBall);	

	double GetRadius() { return radius;};
	int GetType() { return type;};
};
