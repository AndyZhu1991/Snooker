#pragma once

#include "Ball.h"
#include "Table.h"
#include "My2DPhyEngine.h"
#include "SnookerSurface.h"

class SnookerGame
{
public:
	static const int BALL_COUNT = 22;

public:
	Ball* balls[22];
	int intervalTime;  // ms

private:
	SnookerSurface* surface;
	My2DPhyEngine engine;
	Table table;
	bool isBallsStop;

public:
	SnookerGame(SnookerSurface* surface);
	void InitGame();
	void InitBalls();
	void InitEngine();
	void HitMotherBall(double speedValue, double radian);
	void HitMotherBall(Speed speed);
	void onTimer();
	void Calc1Tick();

private:
	void StartTimer();
	void KillTimer();
	void onBallsStop();
};