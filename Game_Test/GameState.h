#pragma once
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameWindows.h"
class GameState
{
private:

public:
	virtual ~GameState();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void draw() = 0;
	virtual void release() = 0;
	virtual void loadScene();

};