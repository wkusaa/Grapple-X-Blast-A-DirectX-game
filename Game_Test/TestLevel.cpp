#include "TestLevel.h"

TestLevel::TestLevel()
{
	std::cout << "TestLevel constructed" << std::endl;
	texture = NULL;
	sprite = NULL;
	playerPos = D3DXVECTOR3(0, 0, 0);
	spriteRect.left = 189;
	spriteRect.top = 196;
	spriteRect.right = 310;
	spriteRect.bottom = 320;
}

TestLevel::~TestLevel()
{
	std::cout << "TestLevel destroyed" << std::endl;
}

void TestLevel::init()
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(GameGraphics::getInstance()->d3dDevice, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(GameGraphics::getInstance()->d3dDevice, "images/militia.png", &texture);
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

	D3DXVECTOR2 spriteCentre2D = D3DXVECTOR2(256.0f, 256.0f);
	D3DXVECTOR2 trans = D3DXVECTOR2(0.0f, 0.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, &spriteCentre2D, NULL, &D3DXVECTOR2(playerPos.x, playerPos.y));
	//std::cout << playerPos.x << "|" << playerPos.y << std::endl;

}

void TestLevel::fixedUpdate()
{

}

void TestLevel::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//D3DXVECTOR3 spriteCentre3D = D3DXVECTOR3(256.0f, 256.0f, 0.0f);

	// Tell the sprite about the matrix
	sprite->SetTransform(&mat);
	
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	sprite->End();
}

void TestLevel::release()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}
