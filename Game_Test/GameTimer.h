#pragma once
#include <winnt.h>
#include <profileapi.h>
//FrameTimer.h
class GameTimer {

private:
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	int Requested_FPS;
	float intervalsPerFrame;

public:
	void init(int fps);
	int framesToUpdate();
};



