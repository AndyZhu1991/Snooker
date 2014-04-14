#include "stdafx.h"
#include "Ball.h"
#include "Point.h"
#include <math.h>

const double Ball::STD_BALL_WEIGHT = 1.0;

double Ball::Distance(Ball& otherBall)
{
	return Point::Distance(x, y, otherBall.x, otherBall.y);
}
