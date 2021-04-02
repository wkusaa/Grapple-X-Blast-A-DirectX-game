#include "TestLevel4.h"

TestLevel4::TestLevel4()
{
	std::cout << "TestLevel4 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);

	collision = new CollisionManager;

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

	for (int i = 0; i < ammoArray.size(); i++)
	{
		delete ammoArray[i];
		ammoArray[i] = NULL;
	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		delete gemsArray[i];
		gemsArray[i] = NULL;
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

	delete key1;
	delete gate;

	delete collision;
}

void TestLevel4::init()
{

}

void TestLevel4::update()
{

}

void TestLevel4::fixedUpdate()
{
	playerCon->Update(grapplePointArray);
	for (int i = 0; i < ammoArray.size(); i++)
	{
		ammoArray[i]->Update();
	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		gemsArray[i]->Update();
	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		spikeArray[i]->Update();
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		brazierArray[i]->Update();
	}

	//---------------------------------------------------------------------

	for (int i = 0; i < platformArray.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), platformArray[i]->position, platformArray[i]->spriteRect))
		{
			
			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), platformArray[i]->getPosition(), platformArray[i]->getSize());
		}
	}

	for (int i = 0; i < spikeArray.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), spikeArray[i]->position, spikeArray[i]->spriteRect))
		{
			
			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), spikeArray[i]->getPosition(), spikeArray[i]->getSize());
		}
	}

	for (int i = 0; i < brazierArray.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), brazierArray[i]->position, brazierArray[i]->spriteRect))
		{
			
			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), brazierArray[i]->getPosition(), brazierArray[i]->getSize());
		}
	}



	key1->Update();
	gate->Update();

	std::cout << GameStateManager::getInstance()->elapsedTime << std::endl;
}

void TestLevel4::draw()
{
	

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		grapplePointArray[i]->Draw();
	}

	for (int i = 0; i < ammoArray.size(); i++)
	{
		ammoArray[i]->Draw();
	}

	for (int i = 0; i < gemsArray.size(); i++)
	{
		gemsArray[i]->Draw();
	}
	key1->Draw();

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
	playerCon->Draw();
}

void TestLevel4::release()
{

}

void TestLevel4::buildLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	key1 = new Key;
	key1->Initialize(gameGraphics->d3dDevice);
	key1->setPosition(D3DXVECTOR3(247.0f, 629.0f, 0.0f));

	Ammo* am1 = new Ammo(D3DXVECTOR3(200.0f, 500.0f, 0.0f));
	am1->Initialize(gameGraphics->d3dDevice);
	ammoArray.push_back(am1);

	Gems* gem1 = new Gems(D3DXVECTOR3(300.0f, 400.0f, 0.0f));
	Gems* gem2 = new Gems(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
	gem1->Initialize(gameGraphics->d3dDevice);
	gem2->Initialize(gameGraphics->d3dDevice);
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
}

void TestLevel4::loadScene()
{
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
}

