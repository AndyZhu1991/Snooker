#pragma once

#include "Ball.h"
#include "Table.h"
#include "RandomGenerator.h"

class My2DPhyEngine
{
public:
	static const double STD_FRICTION;
	static const double STD_AIR_RESISTANCE;
	static const double G;

private:
	double intervalTime;		// 间隔时间

	double friction;		// 摩擦力系数
	bool enableFriction;

	double airResistance;		// 空气阻力
	bool enableAirResistance;

	double hitEnergyLoss;		// 碰撞能量损失
	bool enableHitEnergyLoss;

	RandomGenerator *pRandomGenerator;
	int randomSeek;
	bool enableRandom;

public:
	My2DPhyEngine();
	
	void SetIntervalTime(double intervalTime);
	void SetIntervalTime(int intervalTime);
	void SetFriction(double friction, bool enable);
	void SetAirResistance(double airResistance, bool enable);
	void SetHitEnergyLoss(double hitEnergyLoss, bool enable);
	void SetRandomGenerator(RandomGenerator* pGenerator,
		int seek, bool enable);

	void BallRun(Ball& ball);
	void BallHitBall(Ball& ball1, Ball& ball2);
	void BallHitTable(Ball& ball, Table& table);
	bool IsBallInTable(Ball& ball, Table& table);

private:
	void BallHitEdge(Ball& ball, Edge* edge);
	void BallHitHEdge(Ball& ball, Edge* edge);
	void BallHitVEdge(Ball& ball, Edge* edge);
	// Point 在圆上
	void BallHitPoint(Ball& ball, Point& point);
	void BallHitPoint(Ball& ball, double x, double y);
};

static double* CalcQEOOU(double a, double b, double c);
