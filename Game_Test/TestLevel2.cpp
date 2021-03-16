#include "TestLevel2.h"

TestLevel2::TestLevel2()
{
	std::cout << "TestLevel2 created" << std::endl;
	Player* player = Player::getInstance();
	player->setPosition(D3DXVECTOR3(50.0f, 720.0f/2, 0.0f));


	gravity = D3DXVECTOR3(0.0f, 0.02f, 0.0f);
	direction = D3DXVECTOR3(sin(D3DXToRadian(90)), -cos(D3DXToRadian(90)), 0.0f);
	line = new DXLine;
	line->createLine(GameGraphics::getInstance()->d3dDevice);
}

TestLevel2::~TestLevel2()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
	Player::getInstance()->ReleaseInstance();
	delete line;
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
		float speed = 10.0f;

		player->velocity = direction * speed;
		direction += gravity;
		player->velocity += gravity;
		player->position += player->velocity;
	}


}

void TestLevel2::draw()
{
	Player::getInstance()->Begin();
	Player::getInstance()->Draw();
	//y=mx
	//float blastOffAngle = Player::getInstance()->getBlastOffAngle();
	D3DXVECTOR3 cannonPos = Player::getInstance()->blastCannon.getPosition();
	int lineScaling = 10;
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;

	//float scalarX = mouseX + (cannonPos.x - mouseX) * lineScaling;
	//float scalarY = mouseY + (cannonPos.y - mouseY) * lineScaling;

	float scalarX = cannonPos.x + (mouseX - cannonPos.x) * lineScaling;
	float scalarY = cannonPos.y + (mouseY - cannonPos.y) * lineScaling;

	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(cannonPos.x, cannonPos.y), D3DXVECTOR2(GameInput::getInstance()->mousePosition.x, GameInput::getInstance()->mousePosition.y) };
	line->draw(lineVertices,2,D3DCOLOR_XRGB(255, 255, 255));
}

void TestLevel2::release()
{

}
