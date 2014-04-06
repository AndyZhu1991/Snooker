#pragma once

#include "Line.h"
#include <list>

class Table
{
private:
	double width;
	double height;

public:
	std::list<Line*> edge;

private:
	void InitEdge();

public:
	Table(double width, double height): width(width), height(height)
	{
		InitEdge();
	};

	double GetWidth() {return width;};
	double GwiHeight() {return height;};
};
