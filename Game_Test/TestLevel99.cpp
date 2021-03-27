#include "TestLevel99.h"

TestLevel99::TestLevel99()
{
	std::cout << "TestLevel99 created" << std::endl;
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	Player* player = Player::getInstance();
	player->setPosition(D3DXVECTOR3(50.0f, 650.0f, 0.0f));

	/*playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/

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
		
	isMoving = true;
	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;

	for (int i = 0; i < 8; i++)
	{
		Grass* grass = new Grass(i * 32, 688, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(512 + i * 32, 688, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(1024 + i * 32, 688, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(i * 32, 144, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Brick* brick = new Brick(256 + i * 32, 176, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);

		Trap* trap = new Trap(i * 32, 176, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		trap = new Trap(256 + i * 32, 64, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		for (int j = 0; j < 2; j++)
		{
			Brick* brick = new Brick(256 + i * 32, j * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}


		Lava* lava = new Lava(256 + i * 32, 688, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(256 + i * 32, 144, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(768 + i * 32, 688, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);
	}

	for (int i = 0; i < 4; i++)
	{
		Grass* grass = new Grass(640 + i * 32, 400, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(896 + i * 32, 112, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Lava* lava = new Lava(768 + i * 32, 496, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(1024 + i * 32, 496, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		for (int j = 0; j < 10; j++)
		{
			Brick* brick = new Brick(640 + i * 32, j * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int j = 0; j < 12; j++)
		{
			Brick* brick = new Brick(896 + i * 32, 144 + j * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int k = 0; k < 3; k++)
		{
			Brick* brick = new Brick(640 + i * 32, 432 + k * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}
	}

	for (int i = 0; i < 37; i++)
	{
		Brick* brick = new Brick(i * 32, 528, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}
	
	for (int i = 0; i < 20; i++)
	{
		Lava* lava = new Lava(i * 32, 496, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		Brick* brick = new Brick(128 + i * 32, 320, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}

	for (int i = 0; i < 16; i++)
	{
		Grass* grass = new Grass(128 + i * 32, 288, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Trap* trap = new Trap(768 + i * 32, 0, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);
	}

	Grass* grass = new Grass(1152, 496, 0);
	grass->Initialize(gameGraphics->d3dDevice);
	grassObject.push_back(grass);

	doorObject = new Door(20, 80, 0);
	doorObject->Initialize(gameGraphics->d3dDevice);
}

TestLevel99::~TestLevel99()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	for (int i = 0; i < brickObject.size(); i++)
	{
		delete brickObject[i];
		brickObject[i] = NULL;
	}

	for (int i = 0; i < grassObject.size(); i++)
	{
		delete grassObject[i];
		grassObject[i] = NULL;
	}

	for (int i = 0; i < lavaObject.size(); i++)
	{
		delete lavaObject[i];
		lavaObject[i] = NULL;
	}

	for (int i = 0; i < trapObject.size(); i++)
	{
		delete trapObject[i];
		trapObject[i] = NULL;
	}

	delete doorObject;
}

void TestLevel99::init()
{
	
}

void TestLevel99::update()
{
	
}

void TestLevel99::fixedUpdate()
{
	/*playerCon->Update(grapplePointArray);*/
	Player* player = Player::getInstance();
	player->Update();
	
	if (player->position.x < 0)
		player->position.x = 1;

	if (player->position.y < 0)
		player->position.y = 1;

	if (player->position.x > 1280)
		player->position.x = 1200;

	/*if (player->position.y > 720)
		player->position.y = 700;*/

	for (int i = 0; i < grassObject.size(); i++)
	{
		if (checkCollision(player->position, player->getBounding_Box(), grassObject[i]->position, grassObject[i]->spriteRect))
		{
			//printf("collide\n");
			
			int side = checkSideCollide(player->position, grassObject[i]->position);
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

	for (int i = 0; i < brickObject.size(); i++)
	{
		if (checkCollision(player->position, player->getBounding_Box(), brickObject[i]->position, brickObject[i]->spriteRect))
		{
			//printf("collide\n");

			int side = checkSideCollide(player->position, brickObject[i]->position);
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

	for (int i = 0; i < trapObject.size(); i++)
	{
		if (checkCollision(player->position, player->getBounding_Box(), trapObject[i]->position, trapObject[i]->getBounding_Box()))
		{
			//printf("collide\n");

			int side = checkSideCollide(player->position, trapObject[i]->position);
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

	for (int i = 0; i < lavaObject.size(); i++)
	{
		if (checkCollision(player->position, player->getBounding_Box(), lavaObject[i]->position, lavaObject[i]->spriteRect))
		{
			printf("collide\n");

			int side = checkSideCollide(player->position, lavaObject[i]->position);
			printf("%d\n", side);

			if (side == 1) //right
			{
				player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
				player->position += (player->velocity);
				isMoving = true;
			}
			else if (side == 2)//top
			{
				player->velocity = D3DXVECTOR3(0.0f, -10.0f, 0);
				player->position += (player->velocity);
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
	
	/*if (GameInput::getInstance()->KeyboardKeyHold(DIK_W))*/
	if (isMoving == true)
	{
		float speed = 3.0f;
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
	Player* player = Player::getInstance();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	for (int i = 0; i < grassObject.size(); i++) {
		grassObject[i]->Render();
	}
	
	for (int i = 0; i < brickObject.size(); i++) {
		brickObject[i]->Render();
	}

	for (int i = 0; i < lavaObject.size(); i++) {
		lavaObject[i]->Render();
	}

	for (int i = 0; i < trapObject.size(); i++) {
		trapObject[i]->Render();
	}

	doorObject->Render();
	player->Draw();

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

int TestLevel99::checkSideCollide(D3DXVECTOR3 player, D3DXVECTOR3 object)
{
	/*D3DXVECTOR3 offset = player - object;
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
	}*/
	
	float player_bottom = player.y + 18;
	float tiles_bottom = object.y + 32;
	float player_right = player.x + 11;
	float tiles_right = object.x + 32;

	float b_collision = tiles_bottom - player.y - 18;
	float t_collision = player_bottom - object.y;
	float l_collision = player_right - object.x;
	float r_collision = tiles_right - player.x - 11;

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
	{
		return 2;
		//Top collision
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
	{
		return 3;
		//bottom collision
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
		return 4;
		//Left collision
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
	{
		return 1;
		//Right collision
	}

	return 0;
}
