#include "stdafx.h"
#include "Point.h"
#include <math.h>

double Point::Distance(Point& otherPoint)
{
	return sqrt((x - otherPoint.x) * (x - otherPoint.x) +
		    (y - otherPoint.y) * (y - otherPoint.y));
}
