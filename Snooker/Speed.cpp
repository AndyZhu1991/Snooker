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

	// 将速度分解

	double radian2;	// radian2是radian的反方向弧度
	if (radian < PI)
	{
		radian2 = radian + PI;
	}
	else
	{
		radian2 = radian - PI;
	}

	// 计算得到那个与当前方向相差PI/2以内的弧度以及弧度差
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
	// Value()*cos(radianDis)是radian方向上的分力
	speeds[0] = Speed::GetSpeedFromValueNRadian(Value()*cos(radianDis), radian);
	speeds[1] = *this - speeds[0];

	return speeds;
}