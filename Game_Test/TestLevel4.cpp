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

	delete key1;
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

	key1->Update();
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
}

void TestLevel4::release()
{

}
