#pragma once
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameWindows.h"
#include "GameSound.h"
class GameState
{
private:

protected:
	GameSound* soundLevel;

public:
	//static GameState* currentScene;
	virtual ~GameState();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void draw() = 0;
	virtual void release() = 0;
	virtual void loadScene();
	virtual void nextScene();

};