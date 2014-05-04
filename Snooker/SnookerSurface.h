#pragma once

class SnookerSurface
{
public:
	virtual void onBallsStop();
	virtual void setTimer(int ms);
	virtual void killTimer();
};