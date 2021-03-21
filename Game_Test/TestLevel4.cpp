#include "TestLevel4.h"

TestLevel4::TestLevel4()
{
	std::cout << "TestLevel4 created" << std::endl;
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(50.0f, 720.0f / 2, 0.0f));


	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

TestLevel4::~TestLevel4()
{
	std::cout << "TestLevel4 destroyed" << std::endl;
}

void TestLevel4::init()
{

}

void TestLevel4::update()
{
	
}

void TestLevel4::fixedUpdate()
{


	playerCon->Update();
}

void TestLevel4::draw()
{
	playerCon->Draw();
}

void TestLevel4::release()
{

}
