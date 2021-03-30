#include "TestLevel4.h"

TestLevel4::TestLevel4()
{
	std::cout << "TestLevel4 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	key1 = new Key;
	key1->Initialize(gameGraphics->d3dDevice);
	key1->setPosition(D3DXVECTOR3(400.0f, 500.0f, 0.0f));

	GrapplingPoint* gp1 = new GrapplingPoint(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	GrapplingPoint* gp2 = new GrapplingPoint(D3DXVECTOR3(400.0f, 720.0f / 2 - 200.0f, 0.0f));
	gp1->Initialize(gameGraphics->d3dDevice);
	gp2->Initialize(gameGraphics->d3dDevice);
	grapplePointArray.push_back(gp1);
	grapplePointArray.push_back(gp2);

	Ammo* am1 = new Ammo(D3DXVECTOR3(200.0f, 400.0f, 0.0f));
	Ammo* am2 = new Ammo(D3DXVECTOR3(100.0f, 200.0f, 0.0f));
	am1->Initialize(gameGraphics->d3dDevice);
	am2->Initialize(gameGraphics->d3dDevice);
	ammoArray.push_back(am1);
	ammoArray.push_back(am2);

	Gems* gem1 = new Gems(D3DXVECTOR3(300.0f, 400.0f, 0.0f));
	Gems* gem2 = new Gems(D3DXVECTOR3(500.0f, 400.0f, 0.0f));
	gem1->Initialize(gameGraphics->d3dDevice);
	gem2->Initialize(gameGraphics->d3dDevice);
	gemsArray.push_back(gem1);
	gemsArray.push_back(gem2);

	Platform* platform1 = new Platform(1, 100, 500, 0);
	Platform* platform2 = new Platform(2, 200, 500, 0);
	Platform* platform3 = new Platform(3, 300, 500, 0);
	Platform* platform4 = new Platform(4, 400, 500, 0);
	Platform* platform5 = new Platform(5, 500, 500, 0);
	platform1->Initialize(gameGraphics->d3dDevice);
	platform2->Initialize(gameGraphics->d3dDevice);
	platform3->Initialize(gameGraphics->d3dDevice);
	platform4->Initialize(gameGraphics->d3dDevice);
	platform5->Initialize(gameGraphics->d3dDevice);
	platformArray.push_back(platform1);
	platformArray.push_back(platform2);
	platformArray.push_back(platform3);
	platformArray.push_back(platform4);
	platformArray.push_back(platform5);
	
	gate = new Gate();
	gate->Initialize(gameGraphics->d3dDevice);
	gate->setPosition(D3DXVECTOR3(WIN_WIDTH - 20.0f, 0.0f + gate->getSize().y/2, 0.0f));

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

	Platform* platform = new Platform(4, WIN_WIDTH - 200.0f, 80.0f, 0.0f);
	platform->Initialize(gameGraphics->d3dDevice);
	platformArray.push_back(platform);

	for (int i = 0; i < 5; i++)
	{
		Spike* spike = new Spike();
		spike->Initialize(gameGraphics->d3dDevice);
		spike->setPosition(D3DXVECTOR3(200.0f + spike->getSize().x * i, 350.0f, 0.0f));
		spikeArray.push_back(spike);
	}

	for (int i = 0; i < 22; i++)
	{
		Brazier* brazier = new Brazier();
		brazier->Initialize(gameGraphics->d3dDevice);
		brazier->setPosition(D3DXVECTOR3(brazier->getSize().x * i, 720.0f, 0.0f));
		brazierArray.push_back(brazier);
	}



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

	key1->Update();
	gate->Update();
}

void TestLevel4::draw()
{
	playerCon->Draw();

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
}

void TestLevel4::release()
{

}
