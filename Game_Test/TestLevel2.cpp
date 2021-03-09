#include "TestLevel2.h"

TestLevel2::TestLevel2()
{
	std::cout << "TestLevel2 created" << std::endl;
	Player* player = player->getInstance();
}

TestLevel2::~TestLevel2()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
	std::cout << "RELEASE!" << std::endl;
	Player::getInstance()->ReleaseInstance();
}

void TestLevel2::init()
{
	Player::getInstance()->Initialize(GameGraphics::getInstance()->d3dDevice);
}

void TestLevel2::update()
{
	
}

void TestLevel2::fixedUpdate()
{
	Player::getInstance()->Update();
}

void TestLevel2::draw()
{

	Player::getInstance()->Begin();
	Player::getInstance()->Draw();
}

void TestLevel2::release()
{

}
