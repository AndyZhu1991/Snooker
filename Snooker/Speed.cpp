#include "stdafx.h"
#include "Speed.h"
#include <math.h>

const double PI = 3.14159265358979323846;

const double Speed::LIMIT_ZERO_SPEED = 0.01;

double Speed::Value()
{
	return sqrt(x*x + y*y);
}

double Speed::Radian()
{
	return atan(y/x);
}

Speed Speed::operator+(const Speed& s)
{
	return Speed(x + s.x, y + s.y);
}

Speed Speed::operator-(const Speed& s)
{
	return Speed(x - s.x, y - s.y);
}

Speed Speed::operator+(double d)
{
	double scale = d / Value();
	return Speed(x * (1 + scale), y * (1 + scale));
}

Speed Speed::operator-(double d)
{
	double scale = d / Value();
	return Speed(x * (1 - scale), y * (1 - scale));
}

Speed Speed::operator*(double d)
{
	return Speed(x * d, y * d);
}

Speed Speed::operator/(double d)
{
	return Speed(x / d, y / d);
}

Speed Speed::GetSpeedFromValueNRadian(double value, double radian)
{
	return Speed(value*cos(radian), value*sin(radian));
}

static double RadianSub(double a, double b)
{
	if (a - b > PI)
	{
		return a - b - 2*PI;
	}

	if (a - b < -PI)
	{
		return a - b + 2*PI;
	}

	return a - b;
}

Speed* Speed::DecSpeed(double radian)
{
	Speed* speeds = new Speed[2];

	// ���ٶȷֽ�

	double radian2;	// radian2��radian�ķ����򻡶�
	if (radian < PI)
	{
		radian2 = radian + PI;
	}
	else
	{
		radian2 = radian - PI;
	}

	// ����õ��Ǹ��뵱ǰ�������PI/2���ڵĻ����Լ����Ȳ�
	double radianDis;
	if (abs(RadianSub(radian, Radian())) < PI/2)
	{
		radianDis = RadianSub(radian, Radian());
	}
	else
	{
		radianDis = RadianSub(radian2, Radian());
		radian = radian2;
	}
	// Value()*cos(radianDis)��radian�����ϵķ���
	speeds[0] = Speed::GetSpeedFromValueNRadian(Value()*cos(radianDis), radian);
	speeds[1] = *this - speeds[0];

	return speeds;
}