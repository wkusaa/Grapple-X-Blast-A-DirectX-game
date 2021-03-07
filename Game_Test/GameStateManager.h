#pragma once
#include "GameState.h"
#include "GameTimer.h"
#include "Level1.h"
#include "TestLevel.h"
#include <vector>
#include <iostream>
class GameStateManager
{
private:

	static GameStateManager* instance;
	GameStateManager();
	~GameStateManager();
public:
	static GameStateManager* getInstance();
	void fixedUpdate();
	void update();
	void draw();
	void release();

	GameTimer* gTimer;
	GameState* currentGameState;
	std::vector<GameState*> gameLevels;

};