#include "TestLevel99.h"

TestLevel99::TestLevel99()
{
	std::cout << "TestLevel2 created" << std::endl;
	Player* player = Player::getInstance();
	player->setPosition(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	sprite = NULL;
	texture = NULL;
	texture_brick = NULL;
	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	direction = D3DXVECTOR3(sin(D3DXToRadian(90)), -cos(D3DXToRadian(90)), 0.0f);

	device = GameGraphics::getInstance()->d3dDevice;

	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFileEx(device, BACKGROUND, D3DX_DEFAULT, D3DX_DEFAULT,
										D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
										D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
										NULL, NULL, &texture);
		
	D3DXCreateTextureFromFileEx(device, BRICK, D3DX_DEFAULT, D3DX_DEFAULT,
										D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
										D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
										NULL, NULL, &texture_brick);
	isMoving = true;
	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;

	rect_brick.left = 0;
	rect_brick.top = 0;
	rect_brick.right = 64;
	rect_brick.bottom = 64;

	for (int i = 0; i < 10; i++)
	{
		brick_pos[i].x = 200 + i * 64;
		brick_pos[i].y = 200;
	}

}

TestLevel99::~TestLevel99()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	texture_brick->Release();
	texture_brick = NULL;

}

void TestLevel99::init()
{
	Player::getInstance()->Initialize(GameGraphics::getInstance()->d3dDevice);
}

void TestLevel99::update()
{
	
}

void TestLevel99::fixedUpdate()
{
	Player* player = Player::getInstance();
	player->Update();
	
	if (player->position.x < 0)
		player->position.x = 1;

	if (player->position.y < 0)
		player->position.y = 1;

	if (player->position.x > 1280)
		player->position.x = 1200;

	if (player->position.y > 720)
		player->position.y = 650;

	for (int i = 0; i < 10; i++)
	{
		if (checkCollision(player->position, player->getBounding_Box(), brick_pos[i], rect_brick))
		{
			//printf("collide\n");
			//player->velocity = D3DXVECTOR3(0.0f,0,0);
			//player->position -= (player->velocity);
			
			int side = checkSideCollide(player->position, brick_pos[i]);
			printf("%d\n", side);
			
			if (side == 1) //right
			{
				player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
				player->position += (player->velocity);
				isMoving = true;
			}	
			else if (side == 2)//top
			{
				player->position -= (player->velocity);
				isMoving = false;
			}
			else if (side == 3)//bottom
			{
				player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
				player->position += (player->velocity);
				isMoving = true;
			}
			else
			{
				player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
				player->position += (player->velocity);
				isMoving = true;
			}
				
		}
		
	}
	
	if (GameInput::getInstance()->MouseButtonClick(0))
	{
		std::cout << "MouseClick" << std::endl;
		float blastOffAngle = player->getBlastOffAngle();
		std::cout << blastOffAngle << std::endl;
		direction = D3DXVECTOR3(sin(blastOffAngle), -cos(blastOffAngle), 0.0f);
		isMoving = true;
	}
	
	//if (GameInput::getInstance()->KeyboardKeyHold(DIK_W))
	if (isMoving == true)
	{
		float speed = 2.0f;
		player->velocity = direction * speed;
		direction += gravity;
		player->velocity += gravity;

		if (player->velocity.x > 10)
			player->velocity.x = 10;

		if (player->velocity.y > 10)
			player->velocity.y = 10;

		player->position += player->velocity;
	}
	
}

void TestLevel99::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	for (int i = 0; i < 10; i++) { 
		sprite->Draw(texture_brick, &rect_brick, NULL, &brick_pos[i], D3DCOLOR_XRGB(255, 255, 255));
	}
	sprite->End();
	
	Player::getInstance()->Draw();
	
}

void TestLevel99::release()
{

}


bool TestLevel99::checkCollision(D3DXVECTOR3 pos1, RECT rect1, D3DXVECTOR3 pos2, RECT rect2)
{
	characterCenter.x = (rect1.right - rect1.left) / 2;
	characterCenter.y = (rect1.bottom - rect1.top) / 2;
	rect1.right = pos1.x + rect1.right - rect1.left - characterCenter.x;
	rect1.left = pos1.x - characterCenter.x;
	rect1.bottom = pos1.y + rect1.bottom - rect1.top - characterCenter.y;
	rect1.top = pos1.y - characterCenter.y;

	rect2.right = pos2.x + rect2.right - rect2.left;
	rect2.left = pos2.x;
	rect2.bottom = pos2.y + rect2.bottom - rect2.top;
	rect2.top = pos2.y;
	
	if (rect1.bottom < rect2.top) return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;
	
	return true;
}

int TestLevel99::checkSideCollide(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 offset = pos1- pos2;
	D3DXVec3Normalize(&offset, &offset);

	if (abs(offset.x) < abs(offset.y))
	{
		if (offset.x > 0)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	else 
	{
		if (offset.y > 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	return 0;
}
