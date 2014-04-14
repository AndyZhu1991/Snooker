#pragma once

class Edge
{
public:
	static const int HORIZONTAL = 0;
	static const int VERTICAL = 1;

private:
	// 如果是水平的，position代表边离y轴的距离，垂直代表离x轴的距离
	double position;
	// 分别代表起点和终点，start < end
	double start;
	double end;
	// HORIZONTAL或VERTICAL
	int orientation;

public:
	Edge(double position, double start, double end, int orientation)
		: position(position), start(start), end(end),
		orientation(orientation) {};
	double GetPosition() { return position;};
	double GetStart() { return start;};
	double GetEnd() { return end;};
	double GetOrientation() { return orientation;};

};
