#include "TestLevel4.h"

TestLevel4::TestLevel4()
{
	std::cout << "TestLevel4 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	collision = new CollisionManager;
	soundLevel = new GameSound(1, "assets/sound/bgm/suspense.mp3", true);

	buildLevel();

}

TestLevel4::~TestLevel4()
{
	std::cout << "TestLevel4 destroyed" << std::endl;

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		delete grapplePointArray[i];
		grapplePointArray[i] = NULL;
	}

	/*for (int i = 0; i < ammoArray.size(); i++)
	{
		delete ammoArray[i];
		ammoArray[i] = NULL;
	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		delete gemsArray[i];
		gemsArray[i] = NULL;
	}*/

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

void TestLevel4::init()
{

}

void TestLevel4::update()
{
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;

	std::cout << mouseX << "|" << mouseY << std::endl;
}

void TestLevel4::fixedUpdate()
{

	playerCon->Update(grapplePointArray);

	for (int i = 0; i < ammoArray.size(); i++)
	{
		ammoArray[i].Update();
		if (collision->checkCollision(playerCon->player, ammoArray[i].position, ammoArray[i].getBounding_Box(), 2, playerCon->aState))
		{
			playerCon->player->updateAmmoAmount(20);
			ammoArray.erase(ammoArray.begin() + i);
		}

	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		gemsArray[i].Update();
		if (collision->checkCollision(playerCon->player, gemsArray[i].position, gemsArray[i].getBounding_Box(), 2, playerCon->aState))
		{
			gemsArray.erase(gemsArray.begin() + i);
		}

	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		spikeArray[i]->Update();
		collision->checkCollision(playerCon->player, spikeArray[i]->position, spikeArray[i]->getBounding_Box(), 0, playerCon->aState);
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		brazierArray[i]->Update();
		collision->checkCollision(playerCon->player, brazierArray[i]->position, brazierArray[i]->getBounding_Box(), 0, playerCon->aState);
	}

	//---------------------------------------------------------------------

	for (int i = 0; i < platformArray.size(); i++)
	{
		collision->checkCollision(playerCon->player, platformArray[i]->position, platformArray[i]->getBounding_Box(), 1, playerCon->aState);
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
		if (collision->checkCollision(playerCon->player, keysArray[i].position, keysArray[i].getBounding_Box(), 2, playerCon->aState))
		{
			playerCon->player->updateKeyAmount(1);
			keysArray.erase(keysArray.begin() + i);
		}
	}


	gate->Update();
	if (collision->checkCollision(playerCon->player, gate->position, gate->getBounding_Box(), 2, playerCon->aState))
	{
		if (playerCon->player->getKeyAmount() > 0)
			nextScene();
		else
			playerCon->player->setShowKeyMsg(true);
			
	}
	//std::cout << GameStateManager::getInstance()->elapsedTime << std::endl;

	if (playerCon->player->getAmmoAmount() < 0)
	{
		GameOver();
	}

}

void TestLevel4::draw()
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
	if (playerCon->player->getShowKeyMsg() == true) playerCon->player->Draw("No Door Key Detected!", 255, 183, 17);
	else
		playerCon->Draw();

	keyUI->Draw();
	ammoUI->Draw();
}

void TestLevel4::release()
{

}

void TestLevel4::buildLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	Key key1;
	key1.Initialize(gameGraphics->d3dDevice);
	key1.setPosition(D3DXVECTOR3(249.0f, 551.0f, 0.0f));
	keysArray.push_back(key1);

	Ammo am1;
	am1.setPosition(D3DXVECTOR3(200.0f, 500.0f, 0.0f));
	am1.Initialize(gameGraphics->d3dDevice);
	ammoArray.push_back(am1);

	Gems gem1, gem2;
	gem1.setPosition(D3DXVECTOR3(300.0f, 400.0f, 0.0f));
	gem2.setPosition(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
	gem1.Initialize(gameGraphics->d3dDevice);
	gem2.Initialize(gameGraphics->d3dDevice);
	gemsArray.push_back(gem1);
	gemsArray.push_back(gem2);

	gate = new Gate();
	gate->Initialize(gameGraphics->d3dDevice);
	gate->setPosition(D3DXVECTOR3(WIN_WIDTH - 20.0f, 0.0f + gate->getSize().y / 2, 0.0f));

	for (int i = 0; i < 3; i++)
	{
		Platform* platform3 = new Platform(3);
		platform3->Initialize(gameGraphics->d3dDevice);
		platform3->setPosition(D3DXVECTOR3(WIN_WIDTH - platform3->getSize().x * i, 272.0f, 0.0f));

		platformArray.push_back(platform3);
	}

	for (int i = 0; i < 11; i++)
	{
		Platform* ceiling = new Platform(3);
		ceiling->Initialize(gameGraphics->d3dDevice);
		ceiling->setPosition(D3DXVECTOR3(WIN_WIDTH - ceiling->getSize().x * i, 10.0f, 0.0f));
		platformArray.push_back(ceiling);
	}

	for (int i = 0; i < 30; i++)
	{
		Spike* spike = new Spike();
		spike->Initialize(gameGraphics->d3dDevice);
		spike->setPosition(D3DXVECTOR3(1004.0f - spike->getSize().x * i, 29.0f, 0.0f));
		spike->scaling.y *= -1;
		spikeArray.push_back(spike);
	}

	Platform* platform = new Platform(4, WIN_WIDTH - 200.0f, 60.0f, 0.0f);
	platform->Initialize(gameGraphics->d3dDevice);
	platformArray.push_back(platform);

	for (int i = 0; i < 3; i++)
	{
		Platform* platform = new Platform(3);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(WIN_WIDTH - 270.0f - platform->getSize().x * i, 160.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 4; i++)
	{
		Spike* spike = new Spike();
		spike->Initialize(gameGraphics->d3dDevice);
		spike->setPosition(D3DXVECTOR3(930.0f - spike->getSize().x * i, 140.0f, 0.0f));
		spikeArray.push_back(spike);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(549.0f, 50.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 2; i++)
	{
		Platform* platform = new Platform(3);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(350.0f - platform->getSize().x * i, 160.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 4; i++)
	{
		Spike* spike = new Spike();
		spike->Initialize(gameGraphics->d3dDevice);
		spike->setPosition(D3DXVECTOR3(270.0f - spike->getSize().x * i, 140.0f, 0.0f));
		spikeArray.push_back(spike);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(4, 190.0f, 280.0f, 0.0f);
		platform->Initialize(gameGraphics->d3dDevice);
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 2; i++)
	{
		Platform* platform = new Platform(3);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(374.0f + platform->getSize().x * i, 558.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 4; i++)
	{
		if (i % 2 != 0)
		{
			Platform* platform = new Platform(5);
			platform->Initialize(gameGraphics->d3dDevice);
			platform->setPosition(D3DXVECTOR3(345.0f + platform->getSize().x * i, 515.0f, 0.0f));
			platformArray.push_back(platform);
		}
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(148.0f, 477.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 2; i++)
	{
		Platform* platform = new Platform(1);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(644.0f + platform->getSize().x * i, 621.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(933.0f + platform->getSize().x * i, 610.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(1033.0f + platform->getSize().x * i, 546.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(1127.0f + platform->getSize().x * i, 490.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(1016.0f, 311.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	for (int i = 0; i < 1; i++)
	{
		Platform* platform = new Platform(5);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(821.0f + platform->getSize().x * i, 395.0f, 0.0f));
		platformArray.push_back(platform);
	}

	for (int i = 0; i < 4; i++)
	{
		Platform* platform = new Platform(4);
		platform->Initialize(gameGraphics->d3dDevice);
		platform->setPosition(D3DXVECTOR3(0.0f, 0.0f + platform->getSize().y * i, 0.0f));
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

void TestLevel4::loadScene()
{
	restartLevel();
	playerCon->SetPlayerIdle();
	playerCon->player->setPosition(D3DXVECTOR3(1002.0f, 124.0f, 0.0f));
	playerCon->player->setAmmoAmount(20);
	playerCon->player->resetKeyAmount();
	soundLevel->play();
	soundLevel->setVolume(0.3f);


	GameGraphics* gameGraphics = GameGraphics::getInstance();
	gameGraphics->r = 163;
	gameGraphics->g = 0;
	gameGraphics->b = 0;
}

void TestLevel4::nextScene()
{
	soundLevel->stop();
	GameStateManager::getInstance()->changeGameState(3);
}

void TestLevel4::GameOver()
{
	playerCon->TriggerDeath();
	soundLevel->stop();
	releaseLevel();
	playerCon->player->setPosition(D3DXVECTOR3(0, 0, 0));
	GameStateManager::getInstance()->levelContinue = 4;
	GameStateManager::getInstance()->changeGameState(2);
	playerCon->player->setAmmoAmount(1);
}

void TestLevel4::restartLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	Key key;
	key.Initialize(gameGraphics->d3dDevice);
	key.setPosition(D3DXVECTOR3(249.0f, 551.0f, 0.0f));
	keysArray.push_back(key);

	for (int i = 0; i < 1; i++)
	{
		Ammo am;
		am.setPosition(D3DXVECTOR3(200.0f, 500.0f, 0.0f));
		am.Initialize(gameGraphics->d3dDevice);
		ammoArray.push_back(am);
	}
}

void TestLevel4::releaseLevel()
{
	ammoArray.clear();
	keysArray.clear();
}