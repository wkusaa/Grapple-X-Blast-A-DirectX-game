#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	Level1* level1 = new Level1;
	level1->init();
	gameLevels.push_back(level1);
	currentGameState = level1;

}

GameStateManager::~GameStateManager()
{
	std::cout << "GameStateManager destroyed" << std::endl;
}

GameStateManager* GameStateManager::getInstance()
{
	if (instance == 0)
	{
		instance = new GameStateManager;
	}

	return instance;
}

void GameStateManager::releaseInstance()
{

	if (instance != 0)
	{

		for (int i = 0; i < gameLevels.size(); i++)
		{
			delete gameLevels[i];
			gameLevels[i] = NULL;
		}
	}
}
