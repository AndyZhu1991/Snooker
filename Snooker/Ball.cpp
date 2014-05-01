#include "stdafx.h"
#include "Ball.h"
#include "Point.h"
#include <math.h>

const double Ball::STD_WEIGHT = 1.0;
const double Ball::STD_RADIUS = 0.02625;	// m

double Ball::Distance(Ball& otherBall)
{
	return Point::Distance(x, y, otherBall.x, otherBall.y);
}
