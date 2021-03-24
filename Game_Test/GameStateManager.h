#pragma once
#include "GameState.h"
#include "GameTimer.h"
#include "Level1.h"
#include "TestLevel.h"
#include "TestLevel2.h"
#include "TestLevel3.h"
#include "TestLevel4.h"
#include "PlayerController.h"
#include "TestLevel99.h"
#include <vector>
#include <iostream>
#define FPS 60.0f

class GameStateManager
{
private:

	static GameStateManager* instance;
	PlayerController* playerController;
	GameStateManager();
	~GameStateManager();
public:
	static GameStateManager* getInstance();
	void fixedUpdate();
	void update();
	void draw();
	void release();

	float elapsedTime;
	//test

	GameTimer* gTimer;
	GameState* currentGameState;
	std::vector<GameState*> gameLevels;

};