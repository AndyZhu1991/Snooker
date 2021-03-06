#pragma once

class Speed
{
public:
	static const double LIMIT_ZERO_SPEED;

public:
	double x;
	double y;

public:
	Speed(): x(0.0), y(0.0){};
	Speed(double x, double y): x(x), y(y){};
	
	Speed operator+(const Speed &s);
	Speed operator-(const Speed &s);
	Speed operator+(double d);
	Speed operator-(double d);
	Speed operator*(double d);
	Speed operator/(double d);

	static Speed GetSpeedFromValueNRadian(double value, double radian);

	double Value();		// 得到速度大小
	double Radian();	// 得到弧度

	// 分解速度，其中一个方向是radian，存在于数组的0下标
	// 另一个方向与radian垂直，存在于数组的1下标
	Speed* DecSpeed(double radian);
	bool IsZero();
};
