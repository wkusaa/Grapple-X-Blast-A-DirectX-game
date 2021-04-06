#pragma once
#include "GameState.h"
#include "GameTimer.h"
#include "PlayerController.h"
#include "TestLevel4.h"
#include "TestLevel5.h"
#include "TestLevel99.h"
#include "TutorialScene.h"
#include "GameOverScene.h"
#include "StartScene.h"
#include "VictoryScene.h"
#include "Crosshair.h"
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
	Crosshair crosshair;
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
	GameState* tempGameState;
	std::vector<GameState*> gameLevels;
	void changeGameState(int index);

};