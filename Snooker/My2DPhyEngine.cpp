#include "stdafx.h"
#include "My2DPhyEngine.h"
#include "Speed.h"
#include "Table.h"
#include "Line.h"
#include <math.h>
#include <list>

My2DPhyEngine::My2DPhyEngine()
{
	enableFriction = false;
	enableAirResistance = false;
	enableHitEnergyLoss = false;
	enableRandom = false;
}

void My2DPhyEngine::SetIntervalTime(double intervalTime)
{
	this->intervalTime = intervalTime;
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
	ball.x += ball.speed.x * intervalTime;
	ball.y += ball.speed.y * intervalTime;

	// 摩擦力
	if (enableFriction)
	{
	}

	// 空气阻力
	if (enableAirResistance)
	{
	}
}

void My2DPhyEngine::BallHitBall(Ball& ball1, Ball& ball2)
{
	if (ball1.Distance(ball2) > ball1.GetRadius() + ball2.GetRadius())
		return ;

	Speed speedDiff = ball1.speed - ball2.speed;
	// 两球心连线的角度
	double radian = Line(Point(ball1.x, ball1.y), Point(ball2.x, ball2.y))
			.GetRadian();
	Speed* speeds = speedDiff.DecSpeed(radian);
	// 弹性碰撞
	ball1.speed = ball1.speed - speeds[0] + 
			(speeds[0] * (ball1.weight-ball2.weight))
			/ (ball1.weight + ball2.weight);
	ball2.speed = ball2.speed +
		speeds[0] * 2*ball1.weight / (ball1.weight + ball2.weight);
}

void My2DPhyEngine::BallHitTable(Ball& ball, Table& table)
{
	for (std::list<Edge*>::iterator it = table.edges.begin();
		it != table.edges.end(); it++)
	{
		if ((*it)->GetOrientation() == Edge::HORIZONTAL &&
			abs((*it)->GetPosition() - ball.y) < ball.GetRadius())
		{
			if (ball.x > (*it)->GetStart() && ball.x < (*it)->GetEnd())
			{
				ball.speed.y = -ball.speed.y;
				return ;
			}
			else if (Point::Distance(ball.x, ball.y, (*it)->GetStart(),
				(*it)->GetPosition()) < ball.GetRadius())
			{
			}
			else if (Point::Distance(ball.x, ball.y, (*it)->GetEnd(),
				(*it)->GetPosition()) < ball.GetRadius())
			{
			}

		}
		else if ((*it)->GetOrientation() == Edge::VERTICAL &&
			abs((*it)->GetPosition() - ball.x) < ball.GetRadius())
		{
			if (ball.y > (*it)->GetStart() && ball.y < (*it)->GetEnd())
			{
				ball.speed.x = -ball.speed.x;
				return ;
			}
			else if (Point::Distance(ball.x, ball.y, (*it)->GetPosition(),
				(*it)->GetStart()) < ball.GetRadius())
			{
			}
			else if (Point::Distance(ball.x, ball.y, (*it)->GetPosition(),
				(*it)->GetEnd()) < ball.GetRadius())
			{
			}
		}
	}
}
