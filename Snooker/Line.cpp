#include "stdafx.h"
#include "Line.h"
#include <math.h>

void Line::CalcAnB()
{
	a = (start.GetY() - end.GetY()) / (start.GetX() - end.GetX());
	b = start.GetY() - a * start.GetX();
}

double Line::GetRadian()
{
	return atan(a);
}
