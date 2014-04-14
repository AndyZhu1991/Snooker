#include "stdafx.h"
#include "Point.h"
#include <math.h>

double Point::Distance(double x1, double y1, double x2, double y2)
{
	return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));
}

double Point::Distance(Point& otherPoint)
{
	return Distance(x, y, otherPoint.x, otherPoint.y);
}
