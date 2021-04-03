#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	std::cout << "GameStateManager constructed" << std::endl;
	Level1* level1 = new Level1;
	TestLevel* testLevel = new TestLevel;
	TestLevel2* testLevel2 = new TestLevel2;
	TestLevel3* testLevel3 = new TestLevel3;
	TestLevel4* testLevel4 = new TestLevel4;
	TestLevel99* testLevel99 = new TestLevel99;
	StartScene* startScene = new StartScene;
	GameOverScene* gameOver = new GameOverScene;
	VictoryScene* victory = new VictoryScene;
	level1->init();
	testLevel->init();
	testLevel2->init();
	testLevel3->init();
	testLevel4->init();
	testLevel99->init();
	startScene->init();
	gameOver->init();
	victory->init();
	gameLevels.push_back(level1);
	gameLevels.push_back(testLevel);
	gameLevels.push_back(testLevel2);
	gameLevels.push_back(testLevel3);
	gameLevels.push_back(testLevel4);
	gameLevels.push_back(testLevel99);
	gameLevels.push_back(startScene);
	gameLevels.push_back(gameOver);
	gameLevels.push_back(victory);

	currentGameState = gameLevels[5];
	tempGameState = currentGameState;
	currentGameState->loadScene();

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

	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_F))
	{
		currentGameState = gameLevels[5];
	}

	if (currentGameState != tempGameState)
	{
		currentGameState->loadScene();
		tempGameState = currentGameState;
		std::cout << "Switch" << std::endl;
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
