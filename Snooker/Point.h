#pragma once

class Point
{
private:
	double x;
	double y;

public:
	Point(double x, double y): x(x), y(y) {};

	static double Distance(double x1, double y1,
				double x2, double y2);
	double Distance(Point& otherPoint);

	double GetX() { return x;};
	double GetY() { return y;};
};
