#include "stdafx.h"
#include "My2DPhyEngine.h"
#include <math.h>

My2DPhyEngine::My2DPhyEngine()
{
	enableFriction = false;
	enableAirResistance = false;
	enableHitEnergyLoss = false;
	enableRandom = false;
}

void My2DPhyEngine::SetFriction(double friction, bool enable = true)
{
	this->friction = friction;
	this->enableFriction = enable;
}

void My2DPhyEngine::SetAirResistance(double airResistance, bool enable = true)
{
	this->airResistance = airResistance;
	this->enableAirResistance = enable;
}

void My2DPhyEngine::SetHitEnergyLoss(double hitEnergyLoss, bool enable = false)
{
	this->hitEnergyLoss = hitEnergyLoss;
	this->enableHitEnergyLoss = enable;
}

void My2DPhyEngine::SetRandomGenerator(
	RandomGenerator* pGenerator,int seek, bool enable = true)
{
	this->pRandomGenerator = pGenerator;
	this->randomSeek = seek;
	this->enableRandom = enable;
}


void My2DPhyEngine::BallRun(Ball& ball)
{

}

void My2DPhyEngine::BallHitBall(Ball& ball1, Ball& ball2)
{
}

void My2DPhyEngine::BallHitEdge(Ball& ball, Table& table)
{
}
