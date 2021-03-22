#include "TestLevel2.h"

TestLevel2::TestLevel2()
{
	std::cout << "TestLevel2 created" << std::endl;
	Player* player = Player::getInstance();
	player->setPosition(D3DXVECTOR3(50.0f, 720.0f/2, 0.0f));


	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}

TestLevel2::~TestLevel2()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
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
	float magnitude = 20.0f;
	Player* player = Player::getInstance();
	player->Update();

	if (GameInput::getInstance()->MouseButtonClick(0))
	{
		std::cout << "MouseClick" << std::endl;
		float blastOffAngle = player->getBlastOffAngle();
		std::cout << blastOffAngle << std::endl;
		direction = D3DXVECTOR3(sin(blastOffAngle), -cos(blastOffAngle), 0.0f);
	}

	//if (GameInput::getInstance()->KeyboardKeyHold(DIK_W))
	{
		//hoho
		player->velocity = direction * magnitude;
		direction += gravity;
		player->velocity += gravity;
		player->position += player->velocity;
	}

}

void TestLevel2::draw()
{
	//Player::getInstance()->Begin();
	Player::getInstance()->Draw();

}

void TestLevel2::release()
{

}
