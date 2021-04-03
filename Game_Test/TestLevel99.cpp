#include "TestLevel99.h"

TestLevel99::TestLevel99()
{
	std::cout << "TestLevel99 created" << std::endl;
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(50.0f, 650.0f, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0,0,0);
	playerCon->player->velocity = D3DXVECTOR3(0, 0.3, 0);
	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);

	sprite = NULL;
	texture = NULL;

	device = GameGraphics::getInstance()->d3dDevice;
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFileEx(device, BACKGROUND, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;

	buildLevel();
}

TestLevel99::~TestLevel99()
{
	std::cout << "TestLevel2 destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	delete collision;

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

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		delete grapplePointArray[i];
		grapplePointArray[i] = NULL;
	}

	for (int i = 0; i < ammoObject.size(); i++)
	{
		delete ammoObject[i];
		ammoObject[i] = NULL;
	}

	delete doorObject;
	delete keyUI;
	delete ammoUI;
	delete key;
}

void TestLevel99::init()
{
	
}

void TestLevel99::update()
{
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;
	
	//std::cout << mouseX << "|" << mouseY << std::endl;
}

void TestLevel99::fixedUpdate()
{
	
	playerCon->Update(grapplePointArray);
	
	if (playerCon->player->position.x < 0)
		playerCon->player->position.x = 1;

	if (playerCon->player->position.y < 0)
		playerCon->player->position.y = 1;

	if (playerCon->player->position.x > 1280)
		playerCon->player->position.x = 1200;

	if (playerCon->player->position.y > 720)
		playerCon->player->position.y = 650;

	for (int i = 0; i < grassObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), grassObject[i]->position, grassObject[i]->spriteRect))
		{
			
			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), grassObject[i]->getPosition(), grassObject[i]->getSize());
			//printf("grass side %d\n", side);
			
			/*if (side == 1) 
			{
				playerCon->player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
				playerCon->player->position += (playerCon->player->velocity);
				isMoving = true;
			}	
			else if (side == 2)
			{
				playerCon->player->position -= (playerCon->player->velocity);
				isMoving = false;
			}
			else if (side == 3)
			{
				playerCon->player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
				playerCon->player->position += (playerCon->player->velocity);
				isMoving = true;
			}
			else
			{
				playerCon->player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
				playerCon->player->position += (playerCon->player->velocity);
				isMoving = true;
			}*/
		}

	}

	for (int i = 0; i < brickObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), brickObject[i]->position, brickObject[i]->spriteRect))
		{
			
			//printf("collide\n");

			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), brickObject[i]->getPosition(), brickObject[i]->getSize());
			//printf("brick side %d\n", side);

			//if (side == 1) //right
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else if (side == 2)//top
			//{
			//	playerCon->player->position -= (playerCon->player->velocity);
			//	isMoving = false;
			//}
			//else if (side == 3)//bottom
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
		}
	}

	for (int i = 0; i < trapObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), trapObject[i]->position, trapObject[i]->getBounding_Box()))
		{
			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), trapObject[i]->getPosition(), trapObject[i]->getSize());
			//printf("trap side %d\n", side);

			//if (side == 1) //right
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else if (side == 2)//top
			//{
			//	playerCon->player->position -= (playerCon->player->velocity);
			//	isMoving = false;
			//}
			//else if (side == 3)//bottom
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else if (side == 4)
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
		}
	}

	for (int i = 0; i < lavaObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), lavaObject[i]->position, lavaObject[i]->spriteRect))
		{
			//printf("collide\n");

			int side = collision->checkSideCollide(playerCon->player->getPosition(), playerCon->player->getPlayerBbSize(), lavaObject[i]->getPosition(), lavaObject[i]->getSize());
			//printf("water side %d\n", side);

			//if (side == 1) //right
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else if (side == 2)//top
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(0.0f, -10.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = false;
			//}
			//else if (side == 3)//bottom
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
			//else
			//{
			//	playerCon->player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
			//	playerCon->player->position += (playerCon->player->velocity);
			//	isMoving = true;
			//}
		}
	}
	if (collision->checkCollision(playerCon->player->position, playerCon->player->getBounding_Box(), doorObject->position, doorObject->spriteRect))
	{
		GameStateManager::getInstance()->changeGameState(7);
	}

	if (ammoUI->ammoAmount < 0)
	{
		GameStateManager::getInstance()->changeGameState(7);
	}
		
}

void TestLevel99::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	for (int i = 0; i < grassObject.size(); i++) {
		grassObject[i]->Draw();
	}
	
	for (int i = 0; i < brickObject.size(); i++) {
		brickObject[i]->Draw();
	}

	for (int i = 0; i < lavaObject.size(); i++) {
		lavaObject[i]->Draw();
	}

	for (int i = 0; i < trapObject.size(); i++) {
		trapObject[i]->Draw();
	}

	/*for (int i = 0; i < grapplePointArray.size(); i++)
	{
		grapplePointArray[i]->Draw();
	}*/

	for (int i = 0; i < ammoObject.size(); i++)
	{
		ammoObject[i]->Draw();
	}

	doorObject->Draw();
	keyUI->render();
	ammoUI->render();
	playerCon->Draw();
	key->Draw();

}

void TestLevel99::release()
{

}

void TestLevel99::buildLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	for (int i = 0; i < 8; i++)
	{
		Grass* grass = new Grass(16 + i * 32, 704, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(528 + i * 32, 704, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(1040 + i * 32, 704, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(16 + i * 32, 160, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Brick* brick = new Brick(272 + i * 32, 192, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);

		Trap* trap = new Trap(16 + i * 32, 192, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		trap = new Trap(272 + i * 32, 80, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		for (int j = 0; j < 2; j++)
		{
			Brick* brick = new Brick(272 + i * 32, 16 + j * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}


		Lava* lava = new Lava(272 + i * 32, 704, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(272 + i * 32, 160, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(784 + i * 32, 704, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);
	}

	for (int i = 0; i < 4; i++)
	{
		Grass* grass = new Grass(656 + i * 32, 416, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(912 + i * 32, 128, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Lava* lava = new Lava(784 + i * 32, 512, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(1024 + 16 + i * 32, 496 + 16, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		Ammo* ammo = new Ammo(D3DXVECTOR3(80 + i*96, 448.0f, 0.0f));
		ammo->Initialize(gameGraphics->d3dDevice);
		ammoObject.push_back(ammo);

		ammo = new Ammo(D3DXVECTOR3(1230.0f, 512.0f - i * 96, 0.0f));
		ammo->Initialize(gameGraphics->d3dDevice);
		ammoObject.push_back(ammo);

		for (int j = 0; j < 10; j++)
		{
			Brick* brick = new Brick(640 + 16 + i * 32, j * 32 + 16, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int j = 0; j < 12; j++)
		{
			Brick* brick = new Brick(896 + 16 + i * 32, 144 + 16 + j * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int k = 0; k < 3; k++)
		{
			Brick* brick = new Brick(640 + 16 + i * 32, 432 + 16 + k * 32, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}
	}

	for (int i = 0; i < 37; i++)
	{
		Brick* brick = new Brick(i * 32 + 16, 528 + 16, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		Lava* lava = new Lava(i * 32 + 16, 496 + 16, 0);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		Brick* brick = new Brick(128 + 16 + i * 32, 320 + 16, 0);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}

	for (int i = 0; i < 16; i++)
	{
		Grass* grass = new Grass(128 + 16 + i * 32, 288 + 16, 0);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Trap* trap = new Trap(768 + 16 + i * 32, 0 + 16, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(549.0f, 50.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	Grass* grass = new Grass(1152 + 16, 496 + 16, 0);
	grass->Initialize(gameGraphics->d3dDevice);
	grassObject.push_back(grass);

	doorObject = new Door(50 + 16, 80 + 16, 0);
	doorObject->Initialize(gameGraphics->d3dDevice);

	key = new Key();
	key->setPosition(D3DXVECTOR3(832, 448, 0));
	key->Initialize(gameGraphics->d3dDevice);

	keyUI = new KeyUI(D3DXVECTOR3(128.0f, 16.0f, 0.0f));
	keyUI->Initialize(gameGraphics->d3dDevice);

	ammoUI = new AmmoUI(D3DXVECTOR3(16.0f, 16.0f, 0.0f));
	ammoUI->Initialize(gameGraphics->d3dDevice);
}

