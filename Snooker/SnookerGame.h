#pragma once

#include "Ball.h"

class SnookerGame
{
public:
	static const int BALL_COUNT = 22;

public:
	Ball* balls[22];

public:
	SnookerGame();
	void InitBalls();
};