#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	std::cout << "GameStateManager constructed" << std::endl;

	TestLevel4* testLevel4 = new TestLevel4;
	TestLevel99* testLevel99 = new TestLevel99;
	TestLevel5* testLevel5 = new TestLevel5;
	StartScene* startScene = new StartScene;
	GameOverScene* gameOver = new GameOverScene;
	VictoryScene* victory = new VictoryScene;
	TutorialScene* tutorial = new TutorialScene;

	testLevel4->init();
	testLevel99->init();
	startScene->init();
	gameOver->init();
	victory->init();
	tutorial->init();
	testLevel5->init();

	gameLevels.push_back(startScene); //0
	gameLevels.push_back(tutorial);//1
	gameLevels.push_back(gameOver); //2
	gameLevels.push_back(victory); //3
	gameLevels.push_back(testLevel4); // 4 Level 3
	gameLevels.push_back(testLevel99); // 5 Level 1
	gameLevels.push_back(testLevel5); // 6 Level 2


	currentGameState = gameLevels[0];
	tempGameState = currentGameState;
	currentGameState->loadScene();

	levelContinue = 5;

	gTimer = new GameTimer;
	gTimer->init(FPS);

	elapsedTime = 0;

	playerController = PlayerController::getInstance();
	playerController->Initialize();

	crosshair.Initialize(GameGraphics::getInstance()->d3dDevice);


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
	playerController->ReleaseInstance();

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
		elapsedTime += (1.0f / FPS);
		currentGameState->fixedUpdate();
	}

	crosshair.Update();
}

void GameStateManager::update()
{
	if (currentGameState != tempGameState)
	{
		currentGameState->loadScene();
		tempGameState = currentGameState;
	}
	currentGameState->update();

}

void GameStateManager::draw()
{
	currentGameState->draw();
	crosshair.Draw();
}

void GameStateManager::release()
{
	//currentGameState->release();
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void GameStateManager::changeGameState(int index)
{
	currentGameState = gameLevels[index];
}
