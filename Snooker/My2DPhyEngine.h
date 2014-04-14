#pragma once

#include "Ball.h"
#include "Table.h"
#include "RandomGenerator.h"

class My2DPhyEngine
{
private:
	double intervalTime;		// ���ʱ��

	double friction;		// Ħ����ϵ��
	bool enableFriction;

	double airResistance;		// ��������
	bool enableAirResistance;

	double hitEnergyLoss;		// ��ײ������ʧ
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
