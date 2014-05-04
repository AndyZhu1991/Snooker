#include "stdafx.h"
#include "My2DPhyEngine.h"
#include "Speed.h"
#include "Table.h"
#include "Line.h"
#include <math.h>
#include <list>
#include <iostream>

const double My2DPhyEngine::STD_FRICTION = 1.0;
const double My2DPhyEngine::STD_AIR_RESISTANCE = 0.5;

My2DPhyEngine::My2DPhyEngine()
{
	enableFriction = true;
	friction = STD_FRICTION;
	enableAirResistance = true;
	airResistance = STD_AIR_RESISTANCE;
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
		ball.speed = ball.speed - friction * intervalTime;
		//	friction * ball.weight / ball.weight * intervalTime;
	}

	// 空气阻力
	if (enableAirResistance)
	{
		double ballSpeedValue = ball.speed.Value();
		ball.speed = ball.speed -
			airResistance * ballSpeedValue * ballSpeedValue / ball.weight * intervalTime;
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
		BallHitEdge(ball, *it);
	}
}

void My2DPhyEngine::BallHitEdge(Ball& ball, Edge* edge)
{
	if (edge->GetOrientation() == Edge::HORIZONTAL &&
		abs(edge->GetPosition() - ball.y) < ball.GetRadius())
	{
		BallHitHEdge(ball, edge);
	}
	else if (edge->GetOrientation() == Edge::VERTICAL &&
		abs(edge->GetPosition() - ball.x) < ball.GetRadius())
	{
		BallHitVEdge(ball, edge);
	}
}

void My2DPhyEngine::BallHitHEdge(Ball& ball, Edge* edge)
{
	if (ball.x > edge->GetStart() && ball.x < edge->GetEnd())
	{
		ball.speed.y = -ball.speed.y;
		return ;
	}
	else if ((Point::Distance(ball.x, ball.y, edge->GetStart(),
		edge->GetPosition()) < ball.GetRadius()) ||
		(Point::Distance(ball.x, ball.y, edge->GetEnd(),
		edge->GetPosition()) < ball.GetRadius()))
	{
		// (X-a)^2 + (Y-b)^2 = r^2
		//                         ==> X^2 - 2aX + a^2+(p-b)^2-r^2 = 0
		// Y = p
		double a = ball.x, b = ball.y, p = edge->GetPosition(), r = ball.GetRadius();
		double* xs = CalcQEOOU(1.0, 2*a, a*a + (p-b)*(p-b) - r*r);
		if (xs == NULL)
		{
			std::cout<<"in BallHitHEdge(): xs == NULL, "
				<<"a="<<a<<", b="<<b<<", p="<<p<<", r="<<r<<std::endl;
			return ;
		}
		for (int i = 0; i < 2; i++)
		{
			if (xs[i] > edge->GetStart() && xs[i] < edge->GetEnd())
			{
				BallHitPoint(ball, xs[i], edge->GetPosition());
			}
		}
	}
}

void My2DPhyEngine::BallHitVEdge(Ball& ball, Edge* edge)
{
	if (ball.y > edge->GetStart() && ball.y < edge->GetEnd())
	{
		ball.speed.x = -ball.speed.x;
		return ;
	}
	else if ((Point::Distance(ball.x, ball.y, edge->GetPosition(),
		edge->GetStart()) < ball.GetRadius()) ||
		(Point::Distance(ball.x, ball.y, edge->GetPosition(),
		edge->GetEnd()) < ball.GetRadius()))
	{
		// (X-a)^2 + (Y-b)^2 = r^2
		//                         ==> Y^2 - 2bY + b^2+(p-a)^2-r^2 = 0
		// X = p
		double a = ball.x, b = ball.y, p = edge->GetPosition(), r = ball.GetRadius();
		double* ys = CalcQEOOU(1.0, 2*b, b*b + (p-a)*(p-a) - r*r);
		if (ys == NULL)
		{
			std::cout<<"in BallHitVEdge(): xs == NULL, "
				<<"a="<<a<<", b="<<b<<", p="<<p<<", r="<<r<<std::endl;
			return ;
		}
		for (int i = 0; i < 2; i++)
		{
			if (ys[i] > edge->GetStart() && ys[i] < edge->GetEnd())
			{
				BallHitPoint(ball, edge->GetPosition(), ys[i]);
			}
		}
	}
}

void My2DPhyEngine::BallHitPoint(Ball& ball, Point& point)
{
	BallHitPoint(ball, point.GetX(), point.GetY());
}

void My2DPhyEngine::BallHitPoint(Ball& ball, double x, double y)
{
	Speed* speeds = ball.speed.DecSpeed(Line(ball.x, ball.y, x, y).GetRadian());

	// 球正在接近点
	if ((x-ball.x) / speeds[0].x > 0.0)
	{
		ball.speed = ball.speed - speeds[0]*2;
	}
}

bool My2DPhyEngine::IsBallInTable(Ball& ball, Table& table)
{
	if (ball.x > 0 && ball.x < table.GetWidth() &&
		ball.y > 0 && ball.y < table.GwiHeight())
	{
		return true;
	}

	return false;
}

// 计算一元二次方程(quadratic equation of one unknown)
// ax^2 + bx + c = 0
static double* CalcQEOOU(double a, double b, double c)
{
	double delta = b*b - 4*a*c < 0.0;
	if (delta < 0.0)
	{
		return NULL;
	}

	double* result = new double[2];
	result[0] = (-b + sqrt(delta)) / (2 * a);
	result[1] = (-b - sqrt(delta)) / (2 * a);
	return result;
}
