#include "TestLevel.h"

TestLevel::TestLevel()
{
	std::cout << "TestLevel constructed" << std::endl;
	texture = NULL;
	sprite = NULL;

	spriteCentre2D = D3DXVECTOR2(256.0f, 256.0f);
	scaling = D3DXVECTOR2(5.0f, 5.0f);
	spriteCentre3D = D3DXVECTOR3(256.0f, 256.0f, 0.0f);
	size = D3DXVECTOR2(128.0f, 128.0f);
	playerPos = D3DXVECTOR3(0, 0, 0);

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.x;
	spriteRect.right = spriteRect.left + size.y;

	animationTimer = 0;
	animationRate = 0.5f / 8;
	currentFrame = 0;
	rotation = 0;

	//Player* player = new Player;
	//player->GetPosition();
	
}

TestLevel::~TestLevel()
{
	std::cout << "TestLevel destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void TestLevel::init()
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(GameGraphics::getInstance()->d3dDevice, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(GameGraphics::getInstance()->d3dDevice, PLAYER_SPRITE, &texture);
}

void TestLevel::update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_Q))
	{
		GameGraphics* gGraphics = gGraphics->getInstance();
		if (gGraphics->d3dPP.Windowed)
		{
			gGraphics->d3dPP.Windowed = false;
			gGraphics->d3dPP.BackBufferFormat = D3DFMT_A8R8G8B8;
			sprite->OnLostDevice();
			gGraphics->d3dDevice->Reset(&gGraphics->d3dPP);
		}
		else if (!gGraphics->d3dPP.Windowed)
		{
			gGraphics->d3dPP.Windowed = true;
			gGraphics->d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
			sprite->OnLostDevice();
			gGraphics->d3dDevice->Reset(&gGraphics->d3dPP);
		}
	}

}

void TestLevel::fixedUpdate()
{
	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &D3DXVECTOR2(playerPos.x, playerPos.y));
	//std::cout << playerPos.x << "|" << playerPos.y << std::endl;

	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationRate)
	{
		animationTimer -= animationRate;
		currentFrame++;
		currentFrame %= 8;
	}

	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

void TestLevel::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->SetTransform(&mat);
	
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	sprite->End();
}

void TestLevel::release()
{

}
