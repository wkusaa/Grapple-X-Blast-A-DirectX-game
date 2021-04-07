#include "TestLevel5.h"

TestLevel5::TestLevel5()
{
	std::cout << "TestLevel5 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	collision = new CollisionManager;
	soundLevel = new GameSound(1, "assets/sound/bgm/Jeremy Blake - Powerup! NO COPYRIGHT 8-bit Music.mp3", true);

	buildLevel();

	isGameOver = false;
}

TestLevel5::~TestLevel5()
{
	std::cout << "TestLevel5 destroyed" << std::endl;

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		delete grapplePointArray[i];
		grapplePointArray[i] = NULL;
	}

	for (int i = 0; i < platformArray.size(); i++)
	{
		delete platformArray[i];
		platformArray[i] = NULL;
	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		delete spikeArray[i];
		spikeArray[i] = NULL;
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		delete brazierArray[i];
		brazierArray[i] = NULL;
	}

	//delete key1;
	delete gate;
	delete ammoUI;
	delete keyUI;
	delete collision;

	delete soundLevel;
}

void TestLevel5::init()
{

}

void TestLevel5::update()
{
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;

	std::cout << mouseX << "|" << mouseY << std::endl;
}

void TestLevel5::fixedUpdate()
{

	playerCon->Update(grapplePointArray);

	for (int i = 0; i < ammoArray.size(); i++)
	{
		ammoArray[i].Update();
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), ammoArray[i].position, ammoArray[i].getBbBoxSize(), ammoArray[i].getObjectType(), playerCon->aState, playerCon->player->velocity))
		{
			playerCon->player->updateAmmoAmount(5);
			ammoArray.erase(ammoArray.begin() + i);
		}

	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		gemsArray[i].Update();
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), gemsArray[i].position, gemsArray[i].getBbBoxSize(), gemsArray[i].getObjectType(), playerCon->aState, playerCon->player->velocity))
		{
			gemsArray.erase(gemsArray.begin() + i);
		}

	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		spikeArray[i]->Update();
		collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), spikeArray[i]->position, spikeArray[i]->getBbBoxSize(), spikeArray[i]->getObjectType(), playerCon->aState, playerCon->player->velocity);
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		brazierArray[i]->Update();
		if(collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), brazierArray[i]->position, brazierArray[i]->getBbBoxSize(), brazierArray[i]->getObjectType(), playerCon->aState, playerCon->player->velocity))
		{
			isGameOver = true;
		}
		
	}

	//---------------------------------------------------------------------

	for (int i = 0; i < platformArray.size(); i++)
	{
		collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), platformArray[i]->position, platformArray[i]->getBbBoxSize(), platformArray[i]->getObjectType(), playerCon->aState, playerCon->player->velocity);
	}

	/*for (int i = 0; i < spikeArray.size(); i++)
	{

	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
	}*/

	for (int i = 0; i < keysArray.size(); i++)
	{
		keysArray[i].Update();
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), keysArray[i].position, keysArray[i].getBbBoxSize(), keysArray[i].getObjectType(), playerCon->aState, playerCon->player->velocity))
		{
			playerCon->player->updateKeyAmount(1);
			keysArray.erase(keysArray.begin() + i);
		}
	}


	gate->Update();
	if (collision->checkCollision(playerCon->player->position, playerCon->player->getPlayerBbSize(), gate->position, gate->getBbBoxSize(), gate->getObjectType(), playerCon->aState, playerCon->player->velocity))
	{
		if (playerCon->player->getKeyAmount() > 0)
		{
			std::cout << "Next Scene" << std::endl;
			playerCon->player->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			nextScene();
		}
		else
			playerCon->player->setShowKeyMsg(true);
	}


	if (playerCon->player->getAmmoAmount() < 0)
	{
		isGameOver = true;
	}

	if (isGameOver)
	{
		GameOver();
	}

}

void TestLevel5::draw()
{


	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		grapplePointArray[i]->Draw();
	}

	for (int i = 0; i < ammoArray.size(); i++)
	{
		ammoArray[i].Draw();
	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		gemsArray[i].Draw();
	}

	for (int i = 0; i < keysArray.size(); i++)
	{
		keysArray[i].Draw();
	}

	for (int i = 0; i < platformArray.size(); i++)
	{
		platformArray[i]->Draw();
	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		spikeArray[i]->Draw();
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		brazierArray[i]->Draw();
	}

	gate->Draw();
	if(playerCon->player->getShowKeyMsg()==true)
	{ 
		playerCon->player->Draw("No Door Key Detected!",255, 0, 0);
	}
	else
	{
		playerCon->Draw();
	}
	
	keyUI->Draw();
	ammoUI->Draw();
}

void TestLevel5::release()
{

}

void TestLevel5::buildLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	gate = new Gate();
	gate->Initialize(gameGraphics->d3dDevice);
	gate->setPosition(D3DXVECTOR3(WIN_WIDTH - 20.0f, 50.0f, 0.0f));

	for (int i = 0; i < 5; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(146.0f + i*202.0f, 453.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}


	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(1);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(1217.0f, 560.0f, 0.0f));
		platformArray.push_back(platform);
	}


	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(1096.0f, 352.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(896.0f, 281.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(696.0f, 271.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(496.0f, 261.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(296.0f, 251.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(1);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(95.0f, 367.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(218.0f, 238.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(345.0f, 149.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(551.0f, 149.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(757.0f, 149.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(1);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(1217.0f, 210.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(920.0f, 32.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(1);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(92.0f, 670.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 22; i++)
	{
		Brazier* brazier = new Brazier();
		brazier->Initialize(gameGraphics->d3dDevice);
		brazier->setPosition(D3DXVECTOR3(brazier->getSize().x * i, 720.0f, 0.0f));
		brazierArray.push_back(brazier);
	}

	keyUI = new KeyUI(D3DXVECTOR3(164.0f, 50.0f, 0.0f));
	keyUI->Initialize(gameGraphics->d3dDevice);

	ammoUI = new AmmoUI(D3DXVECTOR3(48.0f, 50.0f, 0.0f));
	ammoUI->Initialize(gameGraphics->d3dDevice);
}

void TestLevel5::loadScene()
{

	restartLevel();
	playerCon->SetPlayerIdle();
	playerCon->player->setPosition(D3DXVECTOR3(106.0f, 562.0f, 0.0f));
	playerCon->player->setAmmoAmount(5);
	playerCon->player->resetKeyAmount();
	soundLevel->play();
	soundLevel->setVolume(0.3f);
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	gameGraphics->r = 226;
	gameGraphics->g = 132;
	gameGraphics->b = 49;
}

void TestLevel5::nextScene()
{
	soundLevel->stop();
	GameStateManager::getInstance()->changeGameState(4);
}

void TestLevel5::GameOver()
{
	soundLevel->stop();
	if (playerCon->TriggerDeath(GameStateManager::getInstance()->elapsedTime))
	{
		releaseLevel();
		playerCon->player->setPosition(D3DXVECTOR3(0, 0, 0));
		isGameOver = false;
		GameStateManager::getInstance()->levelContinue = 6;
		GameStateManager::getInstance()->changeGameState(2);
		playerCon->player->setAmmoAmount(5);

	}

}

void TestLevel5::restartLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	Key key1;
	key1.Initialize(gameGraphics->d3dDevice);
	key1.setPosition(D3DXVECTOR3(51.0f, 128.0f, 0.0f));
	keysArray.push_back(key1);

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(549.0f, 579.0f, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(590.0f, 352.0f, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(120.0f, 301.0f, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(903, 409, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(307, 375, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}
}

void TestLevel5::releaseLevel()
{
	ammoArray.clear();
	keysArray.clear();
}

