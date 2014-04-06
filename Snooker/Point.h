#pragma once

class Point
{
private:
	double x;
	double y;

public:
	Point(double x, double y): x(x), y(y) {};

	double Distance(Point& otherPoint);

	double GetX() { return x;};
	double GetY() { return y;};
};
