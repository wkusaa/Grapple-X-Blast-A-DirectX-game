#include "Game.h"

void Game::init()
{
	gWin = gWin->getInstance();
	gWin->createWindow();
	gGraphics = gGraphics->getInstance();
	gGraphics->createDevice();
	gInput = gInput->getInstance();
	gInput->createInput();

	GameSound::Initialize();

	gManager = gManager->getInstance();
}

void Game::update()
{
	while (gWin->gameLoop())
	{
		gInput->update();

		gManager->update();
		gManager->fixedUpdate();

		GameSound::Update();

		gGraphics->beginScene();

		gManager->draw();
		gGraphics->endScene();
	}
}

void Game::release()
{
	gInput->release();
	gGraphics->release();
	gWin->release();
	gManager->release();
	GameSound::Release();
}
