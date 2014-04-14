#pragma once

#include "Edge.h"
#include <list>

class Table
{
private:
	double width;
	double height;

public:
	std::list<Edge*> edges;

private:
	void InitEdges();

public:
	Table(double width, double height): width(width), height(height)
	{
		InitEdges();
	};

	double GetWidth() { return width;};
	double GwiHeight() { return height;};
};
