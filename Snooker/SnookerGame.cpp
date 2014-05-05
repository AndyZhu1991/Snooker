#include "stdafx.h"
#include "SnookerGame.h"
#include "Table.h"
#include <math.h>

#define PI 3.14159265453

const double SnookerGame::RED_BALL_INIT_DIS = 0.001;

SnookerGame::SnookerGame(SnookerSurface* surface)
{
	static const int ballsType[] = { Ball::MOTHER_BALL,
		Ball::YELLOW_BALL, Ball::GREEN_BALL,
		Ball::BROWN_BALL, Ball::BLUE_BALL,
		Ball::PINK_BALL, Ball::BLACK_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL, Ball::RED_BALL,
		Ball::RED_BALL};

	this->surface = surface;
	intervalTime = 3;
	isBallsStop = true;

	for (int i = 0; i < BALL_COUNT; i++)
	{
		balls[i] = new Ball(ballsType[i]);
	}
}

void SnookerGame::InitGame()
{
	InitBalls();
	InitEngine();
}

void SnookerGame::InitBalls()
{
	// Mother ball
	balls[0]->x = Table::START_LINE - Table::D_AREA_RADIUS;
	balls[0]->y = Table::STD_HEIGHT / 2;

	// Yellow ball
	balls[1]->x = Table::START_LINE;
	balls[1]->y = Table::STD_HEIGHT / 2 + Table::D_AREA_RADIUS;

	// Green ball
	balls[2]->x = Table::START_LINE;
	balls[2]->y = Table::STD_HEIGHT / 2 - Table::D_AREA_RADIUS;

	// Brown ball
	balls[3]->x = Table::START_LINE;
	balls[3]->y = Table::STD_HEIGHT / 2;

	// Blue ball
	balls[4]->x = Table::STD_WIDTH / 2;
	balls[4]->y = Table::STD_HEIGHT / 2;

	// Pink Ball
	balls[5]->x = Table::STD_WIDTH / 4 * 3;
	balls[5]->y = Table::STD_HEIGHT / 2;

	// Black ball
	balls[6]->x = Table::STD_WIDTH - Table::BLACK_BALL_POS;
	balls[6]->y = Table::STD_HEIGHT / 2;

	// Red balls
	balls[7]->x = balls[5]->x + Ball::STD_RADIUS / sin(PI / 6) + Ball::STD_RADIUS;
	balls[7]->y = Table::STD_HEIGHT / 2;
	// Init the col 2~5
	for(int pos = 7, i = 1; i <= 4; i++)
	{
		for(int j = 1; j <= i; j++, pos++)
		{
			// 初始化 pos 右上方的那个
			balls[pos+i]->x = balls[pos]->x +
				(Ball::STD_RADIUS + RED_BALL_INIT_DIS / 2) / tan(PI / 6);
			balls[pos+i]->y = balls[pos]->y -
				(Ball::STD_RADIUS + RED_BALL_INIT_DIS / 2);
		}
		// 每一列再加一个
		balls[pos+i]->x = balls[pos]->x;
		balls[pos+i]->y = balls[pos]->y + (Ball::STD_RADIUS * 2 + RED_BALL_INIT_DIS) * i;
	}

	for (int i = 0; i < BALL_COUNT; i++)
	{
		balls[i]->visiable = true;
		balls[i]->speed.x = 0.0;
		balls[i]->speed.y = 0.0;
	}
}

void SnookerGame::InitEngine()
{
	engine.SetIntervalTime(intervalTime);
}

void SnookerGame::HitMotherBall(double speedValue, double radian)
{
	HitMotherBall(Speed::GetSpeedFromValueNRadian(speedValue, radian));
}

void SnookerGame::HitMotherBall(Speed speed)
{
	if (isBallsStop)
	{
		balls[0]->speed = speed;
		isBallsStop = false;
		StartTimer();
	}
}

void SnookerGame::onTimer()
{
	if (!isBallsStop)
	{
		Calc1Tick();
	}
}

void SnookerGame::Calc1Tick()
{
	int stopCount = 0;
	for (int i = 0; i < BALL_COUNT; i++)
	{
		if (balls[i]->visiable)
		{
			engine.BallRun(*balls[i]);
			engine.BallHitTable(*balls[i], table);
			for (int j = i+1; j < BALL_COUNT; j++)
			{
				if (balls[j]->visiable)
				{
					engine.BallHitBall(*balls[i], *balls[j]);
				}
			}
			if (!engine.IsBallInTable(*balls[i], table))
			{
				balls[i]->visiable = false;
			}
		}
		if (!balls[i]->visiable || balls[i]->speed.IsZero())
		{
			stopCount++;
		}
	}
	if (stopCount == BALL_COUNT)
	{
		onBallsStop();
	}
}

void SnookerGame::StartTimer()
{
	surface->setTimer(intervalTime);
}

void SnookerGame::KillTimer()
{
	surface->killTimer();
}

void SnookerGame::onBallsStop()
{
	KillTimer();
}