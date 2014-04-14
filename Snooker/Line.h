#pragma once

#include "Point.h"

class Line
{
private:
	Point start;
	Point end;
	// y = ax + b
	double a;
	double b;

private:
	void CalcAnB();

public:
	Line(Point start, Point end): start(start), end(end) { CalcAnB();};
	Line(double startX, double startY, double endX, double endY)
		: start(startX, startY), end(endX, endY)
	{
		CalcAnB();
	};

	double GetRadian();

	const Point& GetStart() { return start;};
	const Point& GetEnd() { return end;};
};
