#include "stdafx.h"
#include "Table.h"
#include <math.h>

const double Table::STD_WIDTH = 3.569;
const double Table::STD_HEIGHT = 1.778;
const double Table::STD_HOLE_SIZE = 0.085;

void Table::InitEdges()
{
	// Left-Top
	edges.push_back(new Edge(0.0, STD_HOLE_SIZE / sqrt(2),
		STD_WIDTH/2 - STD_HOLE_SIZE/2, Edge::HORIZONTAL));
	// Right-Top
	edges.push_back(new Edge(0.0, STD_WIDTH/2 + STD_HOLE_SIZE/2,
		STD_WIDTH - STD_HOLE_SIZE/sqrt(2), Edge::HORIZONTAL));
	// Left-Bottom
	edges.push_back(new Edge(STD_HEIGHT, STD_HOLE_SIZE / sqrt(2),
		STD_WIDTH/2 - STD_HOLE_SIZE/2, Edge::HORIZONTAL));
	// Right-Bottom
	edges.push_back(new Edge(STD_HEIGHT, STD_WIDTH/2 + STD_HOLE_SIZE/2,
		STD_WIDTH - STD_HOLE_SIZE/sqrt(2), Edge::HORIZONTAL));
	// Left
	edges.push_back(new Edge(0.0, STD_HOLE_SIZE / sqrt(2),
		STD_HEIGHT - STD_HOLE_SIZE/sqrt(2), Edge::VERTICAL));
	// Right
	edges.push_back(new Edge(STD_WIDTH, STD_HOLE_SIZE / sqrt(2),
		STD_HEIGHT - STD_HOLE_SIZE/sqrt(2), Edge::VERTICAL));
}