#include "stdafx.h"
#include "Line.h"

void Line::CalcAnB()
{
	a = (start.GetY() - end.GetY()) / (start.GetX() - end.GetX());
	b = start.GetY() - a * start.GetX();
}
