#include "TestLevel99.h"

TestLevel99::TestLevel99()
{
	playerCon = PlayerController::getInstance();
	playerCon->player->setPosition(D3DXVECTOR3(50.0f, 650.0f, 0.0f));
	playerCon->player->direction = D3DXVECTOR3(0.0f,0.0f,0.0f);
	playerCon->player->velocity = D3DXVECTOR3(0.0f, 0.3f, 0.0f);
	gravity = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	collision = new CollisionManager;
	
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
	
	playerCon->player->setAmmoAmount(200);

	/*ammoObject.clear();
	keyObject.clear();*/
	buildLevel();
}

TestLevel99::~TestLevel99()
{
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

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		delete grapplePointArray[i];
		grapplePointArray[i] = NULL;
	}

	/*for (int i = 0; i < ammoObject.size(); i++)
	{
		delete ammoObject[i];
		ammoObject[i] = NULL;
	}

	for (int i = 0; i < keyObject.size(); i++)
	{
		delete keyObject[i];
		keyObject[i] = NULL;
	}*/
	
	delete doorObject;
	delete keyUI;
	delete ammoUI;
	delete collision;
	
}

void TestLevel99::init()
{
	
}

void TestLevel99::update()
{
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;
}

void TestLevel99::fixedUpdate()
{
	
	playerCon->Update(grapplePointArray);
	
	
	for (int i = 0; i < keyObject.size(); i++)
	{
		keyObject[i].Update();
	}

	for (int i = 0; i < ammoObject.size(); i++)
	{
		ammoObject[i].Update();
	}

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
		collision->checkCollision(playerCon->player, grassObject[i]->position, grassObject[i]->getBounding_Box(), 1, playerCon->aState);
	}
	
	for (int i = 0; i < brickObject.size(); i++)
	{
		collision->checkCollision(playerCon->player, brickObject[i]->position, brickObject[i]->getBounding_Box(), 1, playerCon->aState);
	}

	for (int i = 0; i < trapObject.size(); i++)
	{
		collision->checkCollision(playerCon->player, trapObject[i]->position, trapObject[i]->getBounding_Box(), 0, playerCon->aState);
	}

	for (int i = 0; i < lavaObject.size(); i++)
	{
		collision->checkCollision(playerCon->player, lavaObject[i]->position, lavaObject[i]->getBounding_Box(), 0, playerCon->aState);
	}

	if (collision->checkCollision(playerCon->player, doorObject->position, doorObject->getBounding_Box(), 2, playerCon->aState) && playerCon->player->getKeyAmount() > 0)
	{
		GameStateManager::getInstance()->changeGameState(8);
	}

	for (int i = 0; i < ammoObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player, ammoObject[i].position, ammoObject[i].getBounding_Box(), 2, playerCon->aState))
		{
			playerCon->player->updateAmmoAmount(20);
			ammoObject.erase(ammoObject.begin()+i);
		}
	}

	for (int i = 0; i < keyObject.size(); i++)
	{
		if (collision->checkCollision(playerCon->player, keyObject[i].position, keyObject[i].getBounding_Box(), 2, playerCon->aState))
		{
			playerCon->player->updateKeyAmount(1);
			keyObject.erase(keyObject.begin()+i);
		}
	}

	if (playerCon->player->getAmmoAmount() < 0)
	{
		GameStateManager::getInstance()->changeGameState(7);
		playerCon->player->setAmmoAmount(10);
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

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		grapplePointArray[i]->Draw();
	}

	for (int i = 0; i < ammoObject.size(); i++)
	{
		ammoObject[i].Draw();
	}

	for (int i = 0; i < keyObject.size(); i++)
	{
		keyObject[i].Draw();
	}

	doorObject->Draw();
	keyUI->render();
	ammoUI->render();
	playerCon->Draw();
}

void TestLevel99::release()
{
	
}

void TestLevel99::buildLevel()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();

	for (int i = 0; i < 8; i++)
	{
		Grass* grass = new Grass(16.0f + i * 32.0f, 704.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(528.0f + i * 32.0f, 704.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(1040.0f + i * 32.0f, 704.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(16.0f + i * 32.0f, 160.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Brick* brick = new Brick(272.0f + i * 32.0f, 192.0f, 0.0f);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);

		Trap* trap = new Trap(16.0f + i * 32.0f, 192.0f, 0.0f);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		trap = new Trap(272.0f + i * 32.0f, 80.0f, 0.0f);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);

		for (int j = 0; j < 2; j++)
		{
			Brick* brick = new Brick(272.0f + i * 32.0f, 16.0f + j * 32.0f, 0);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		Lava* lava = new Lava(272.0f + i * 32.0f, 704.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(272.0f + i * 32.0f, 160.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(784.0f + i * 32.0f, 704.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);
	}

	for (int i = 0; i < 4; i++)
	{
		Grass* grass = new Grass(656.0f + i * 32.0f, 416.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		grass = new Grass(912.0f + i * 32.0f, 128.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Lava* lava = new Lava(784.0f + i * 32.0f, 512.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		lava = new Lava(1024.0f + 16.0f + i * 32.0f, 496.0f + 16.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		//Ammo ammo = new Ammo(D3DXVECTOR3(80.0f + i*96.0f, 448.0f, 0.0f));
		//ammo->Initialize(gameGraphics->d3dDevice);
		ammo.setPosition(D3DXVECTOR3(80.0f + i * 96.0f, 448.0f, 0.0f));
		ammo.Initialize(gameGraphics->d3dDevice);
		ammoObject.push_back(ammo);

		//ammo = new Ammo(D3DXVECTOR3(1230.0f, 512.0f - i * 96.0f, 0.0f));
		//ammo->Initialize(gameGraphics->d3dDevice);
		ammo.setPosition(D3DXVECTOR3(1230.0f, 512.0f - i * 96.0f, 0.0f));
		ammo.Initialize(gameGraphics->d3dDevice);
		ammoObject.push_back(ammo);

		for (int j = 0; j < 10; j++)
		{
			Brick* brick = new Brick(640.0f + 16.0f + i * 32.0f, j * 32.0f + 16.0f, 0.0f);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int j = 0; j < 12; j++)
		{
			Brick* brick = new Brick(896.0f + 16.0f + i * 32.0f, 144.0f + 16.0f + j * 32.0f, 0.0f);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}

		for (int k = 0; k < 3; k++)
		{
			Brick* brick = new Brick(640.0f + 16.0f + i * 32.0f, 432.0f + 16.0f + k * 32.0f, 0.0f);
			brick->Initialize(gameGraphics->d3dDevice);
			brickObject.push_back(brick);
		}
	}

	for (int i = 0; i < 37; i++)
	{
		Brick* brick = new Brick(i * 32.0f + 16.0f, 528.0f + 16.0f, 0.0f);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		Lava* lava = new Lava(i * 32.0f + 16.0f, 496.0f + 16.0f, 0.0f);
		lava->Initialize(gameGraphics->d3dDevice);
		lavaObject.push_back(lava);

		Brick* brick = new Brick(128.0f + 16.0f + i * 32.0f, 320.0f + 16.0f, 0.0f);
		brick->Initialize(gameGraphics->d3dDevice);
		brickObject.push_back(brick);
	}

	for (int i = 0; i < 16; i++)
	{
		Grass* grass = new Grass(128.0f + 16.0f + i * 32.0f, 288.0f + 16.0f, 0.0f);
		grass->Initialize(gameGraphics->d3dDevice);
		grassObject.push_back(grass);

		Trap* trap = new Trap(768.0f + 16.0f + i * 32.0f, 16.0f, 0);
		trap->Initialize(gameGraphics->d3dDevice);
		trapObject.push_back(trap);
	}

	for (int i = 0; i < 1; i++)
	{
		GrapplingPoint* gp = new GrapplingPoint(D3DXVECTOR3(549.0f, 50.0f, 0.0f));
		gp->Initialize(gameGraphics->d3dDevice);
		grapplePointArray.push_back(gp);
	}

	Grass* grass = new Grass(1152.0f + 16.0f, 496.0f + 16.0f, 0.0f);
	grass->Initialize(gameGraphics->d3dDevice);
	grassObject.push_back(grass);

	doorObject = new Door(50.0f + 16.0f, 80.0f + 16.0f, 0.0f);
	doorObject->Initialize(gameGraphics->d3dDevice);

	key.setPosition(D3DXVECTOR3(832.0f, 448.0f, 0.0f));
	key.Initialize(gameGraphics->d3dDevice);
	keyObject.push_back(key);

	keyUI = new KeyUI(D3DXVECTOR3(128.0f, 16.0f, 0.0f));
	keyUI->Initialize(gameGraphics->d3dDevice);

	ammoUI = new AmmoUI(D3DXVECTOR3(16.0f, 16.0f, 0.0f));
	ammoUI->Initialize(gameGraphics->d3dDevice);
}


