#pragma once

#include "Ball.h"
#include "Table.h"
#include "My2DPhyEngine.h"
#include "SnookerSurface.h"

class SnookerGame
{
public:
	static const int BALL_COUNT = 22;
	static const double RED_BALL_INIT_DIS;

public:
	Ball* balls[22];
	int intervalTime;  // ms

	bool isBallsStop; // It should be private, just for test

private:
	SnookerSurface* surface;
	My2DPhyEngine engine;
	Table table;

public:
	SnookerGame(SnookerSurface* surface);
	void InitGame();
	void InitBalls();
	void InitEngine();
	void HitMotherBall(double speedValue, double radian);
	void HitMotherBall(Speed speed);
	void onTimer();
	void Calc1Tick();

	void StartTimer();	// Should be private

private:
	void KillTimer();
	void onBallsStop();
};