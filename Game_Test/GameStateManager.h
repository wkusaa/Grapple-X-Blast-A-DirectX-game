#pragma once
#include "GameState.h"
#include "Level1.h"
#include <vector>
#include <iostream>
class GameStateManager
{
private:
	static GameStateManager* instance;
	GameStateManager();
public:

	~GameStateManager();
	static GameStateManager* getInstance();
	void releaseInstance();

	GameState* currentGameState;
	std::vector<GameState*> gameLevels;

};

