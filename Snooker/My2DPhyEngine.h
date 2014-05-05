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
	// Point ��Բ��
	void BallHitPoint(Ball& ball, Point& point);
	void BallHitPoint(Ball& ball, double x, double y);
};

static double* CalcQEOOU(double a, double b, double c);
