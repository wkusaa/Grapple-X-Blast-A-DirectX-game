#pragma once
#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameStateManager.h"
#include "GameSound.h"

class Game
{
private:
	GameWindows* gWin;
	GameGraphics* gGraphics;
	GameInput* gInput;
	GameStateManager* gManager;
public:
	void init();
	void update();
	void release();








};

