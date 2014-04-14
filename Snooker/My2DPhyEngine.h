#pragma once

#include "Ball.h"
#include "Table.h"
#include "RandomGenerator.h"

class My2DPhyEngine
{
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
	void SetFriction(double friction, bool enable);
	void SetAirResistance(double airResistance, bool enable);
	void SetHitEnergyLoss(double hitEnergyLoss, bool enable);
	void SetRandomGenerator(RandomGenerator* pGenerator,
		int seek, bool enable);

	void BallRun(Ball& ball);
	void BallHitBall(Ball& ball1, Ball& ball2);
	void BallHitTable(Ball& ball, Table& table);
};
