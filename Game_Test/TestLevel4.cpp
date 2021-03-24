#include "TestLevel4.h"

TestLevel4::TestLevel4()
{
	std::cout << "TestLevel4 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(50.0f, 720.0f / 2, 0.0f));


	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GameGraphics* gameGraphics = GameGraphics::getInstance();

	GrapplingPoint* gp1 = new GrapplingPoint(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	GrapplingPoint* gp2 = new GrapplingPoint(D3DXVECTOR3(400.0f, 720.0f / 2 - 200.0f, 0.0f));

	gp1->Initialize(gameGraphics->d3dDevice);
	gp2->Initialize(gameGraphics->d3dDevice);

	grapplePointArray.push_back(gp1);
	grapplePointArray.push_back(gp2);

}

TestLevel4::~TestLevel4()
{
	std::cout << "TestLevel4 destroyed" << std::endl;

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		delete grapplePointArray[i];
		grapplePointArray[i] = NULL;
	}
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
}

void TestLevel4::draw()
{
	playerCon->Draw();

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		grapplePointArray[i]->Draw();
	}

}

void TestLevel4::release()
{

}
