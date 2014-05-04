#include "stdafx.h"
#include "Table.h"
#include <math.h>

const double Table::STD_WIDTH = 3.569;
const double Table::STD_HEIGHT = 1.778;
const double Table::STD_HOLE_SIZE = 0.085;

const double Table::START_LINE = 0.737;
const double Table::D_AREA_RADIUS = 0.292;
const double Table::BLACK_BALL_POS = 0.324;

void Table::InitEdges()
{
	// Left-Top
	edges.push_back(new Edge(0.0, holeSize / sqrt(2),
		width/2 - holeSize/2, Edge::HORIZONTAL));
	// Right-Top
	edges.push_back(new Edge(0.0, width/2 + holeSize/2,
		width - holeSize/sqrt(2), Edge::HORIZONTAL));
	// Left-Bottom
	edges.push_back(new Edge(height, holeSize / sqrt(2),
		width/2 - holeSize/2, Edge::HORIZONTAL));
	// Right-Bottom
	edges.push_back(new Edge(height, width/2 + holeSize/2,
		width - holeSize/sqrt(2), Edge::HORIZONTAL));
	// Left
	edges.push_back(new Edge(0.0, holeSize / sqrt(2),
		height - holeSize/sqrt(2), Edge::VERTICAL));
	// Right
	edges.push_back(new Edge(width, holeSize / sqrt(2),
		height - holeSize/sqrt(2), Edge::VERTICAL));
}