#pragma once

#include "Edge.h"
#include <list>

class Table
{
public:
	// Some standard attributes of table
	static const double STD_WIDTH;
	static const double STD_HEIGHT;
	static const double STD_HOLE_SIZE;	// Two times of radius.

	// Ball position
	static const double START_LINE;
	static const double D_AREA_RADIUS;
	static const double BLACK_BALL_POS;

private:
	double width;
	double height;
	double holeSize;

public:
	std::list<Edge*> edges;

private:
	void InitEdges();

public:
	Table(double width = STD_WIDTH, double height = STD_HEIGHT,
		double holeSize = STD_HOLE_SIZE)
		: width(width), height(height), holeSize(holeSize)
	{
		InitEdges();
	};

	double GetWidth() { return width;};
	double GwiHeight() { return height;};
};
