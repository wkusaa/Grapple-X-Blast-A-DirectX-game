#include "TestLevel3.h"

TestLevel3::TestLevel3()
{
	std::cout << "TestLevel3 created" << std::endl;
	Player* player = Player::getInstance();
	player->setPosition(D3DXVECTOR3(50.0f, 720.0f / 2, 0.0f));


	gravity = D3DXVECTOR3(0.0f, 0.02f, 0.0f);
	direction = D3DXVECTOR3(sin(D3DXToRadian(90)), -cos(D3DXToRadian(90)), 0.0f);

	angleDegree = 90;
	swingOppositeDirection = true;
}

TestLevel3::~TestLevel3()
{
	std::cout << "TestLevel3 destroyed" << std::endl;
}

void TestLevel3::init()
{
	Player::getInstance()->Initialize(GameGraphics::getInstance()->d3dDevice);
}

void TestLevel3::update()
{
	Player* player = Player::getInstance();

	D3DXVECTOR3 grapplingPoint = D3DXVECTOR3(WIN_WIDTH / 2, WIN_HEIGHT / 2, 1.0f);
	float distanceFromPoint = 400.0f;

	if (angleDegree > 270)
	{
		swingOppositeDirection = false;
	}
	else if (angleDegree < 90)
	{
		swingOppositeDirection = true;
	}

	if (swingOppositeDirection)
	{
		angleDegree += 1;
	}
	else 
	{
		angleDegree -= 1;
	}

	float angle = D3DXToRadian(angleDegree);

	float offsetX = (sin(angle)) * distanceFromPoint;
	float offsetY = (-cos(angle)) * distanceFromPoint;

	D3DXVECTOR3 currentPosition = D3DXVECTOR3(grapplingPoint.x + offsetX, grapplingPoint.y + offsetY, 1.0f);
	player->setPosition(currentPosition);
}

void TestLevel3::fixedUpdate()
{
	Player* player = Player::getInstance();
	player->Update();


}

void TestLevel3::draw()
{
	Player::getInstance()->Draw();
}

void TestLevel3::release()
{

}
