#pragma once
#include "GameWindows.h"
//FrameTimer.h
class GameTimer {

private:
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	int Requested_FPS;
	float intervalsPerFrame;

public:
	GameTimer();
	~GameTimer();

	void init(int fps);
	int framesToUpdate();
};



