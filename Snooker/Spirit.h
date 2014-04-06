#pragma once

#include "Point.h"

class Spirit
{
public:
	double x;
	double y;
	bool visiable;

public:
	Spirit(): x(0.0), y(0.0), visiable(true) {};
	Spirit(double x, double y, bool visiable = true)
		: x(x), y(y), visiable(visiable) {};
};
