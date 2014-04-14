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
	Speed operator*(double d);
	Speed operator/(double d);

	static Speed GetSpeedFromValueNRadian(double value, double radian);

	double Value();		// �õ��ٶȴ�С
	double Radian();	// �õ�����

	// �ֽ��ٶȣ�����һ��������radian�������������0�±�
	// ��һ��������radian��ֱ�������������1�±�
	Speed* DecSpeed(double radian);
	bool IsZero();
};
