#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	std::cout << "GameStateManager constructed" << std::endl;
	Level1* level1 = new Level1;
	TestLevel* testLevel = new TestLevel;
	level1->init();
	testLevel->init();
	gameLevels.push_back(level1);
	gameLevels.push_back(testLevel);
	currentGameState = gameLevels[1];

	gTimer = new GameTimer;
	gTimer->init(60);

}

GameStateManager::~GameStateManager()
{
	std::cout << "GameStateManager destroyed" << std::endl;
	for (int i = 0; i < gameLevels.size(); i++)
	{
		delete gameLevels[i];
		gameLevels[i] = NULL;
	}

	currentGameState = NULL;
	delete gTimer;
	gTimer = NULL;
}

GameStateManager* GameStateManager::getInstance()
{
	if (!instance)
	{
		instance = new GameStateManager;
	}

	return instance;
}


void GameStateManager::fixedUpdate()
{
	int framesToUpdate = gTimer->framesToUpdate();
	for (int i = 0; i < framesToUpdate; i++)
	{
		currentGameState->fixedUpdate();
	}
}

void GameStateManager::update()
{
	currentGameState->update();
}

void GameStateManager::draw()
{
	currentGameState->draw();
}

void GameStateManager::release()
{

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}