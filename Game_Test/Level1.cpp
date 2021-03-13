#include "Level1.h"
#include <math.h>
//testing
Level1::Level1()
{
	std::cout << "Level1 constructed" << std::endl;
	texture = NULL;
	sprite = NULL;
	playerPos = D3DXVECTOR3(WIN_WIDTH/2, WIN_HEIGHT/2, 0);
	spriteRect.left = 189;
	spriteRect.top = 196;
	spriteRect.right = 310;
	spriteRect.bottom = 320;
}

Level1::~Level1()
{
	std::cout << "Level1 destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void Level1::init()
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(GameGraphics::getInstance()->d3dDevice, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(GameGraphics::getInstance()->d3dDevice, MOSTIMA, &texture);
}

void Level1::update()
{
	float mov = 1.0f;

	if (playerPos.x >= 0 && playerPos.y >= 0 && playerPos.x < WIN_WIDTH && playerPos.y < WIN_HEIGHT)
	{
		D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	}//simple gravity lmao not good for platformers



	if (playerPos.x < 0)
	{
		playerPos.x = 0;
	}

	if (playerPos.y < 0)
	{
		playerPos.y = 0;
	}

	if (playerPos.x > WIN_WIDTH)
	{
		playerPos.y = WIN_WIDTH;
	}

	if (playerPos.y > WIN_HEIGHT)
	{
		playerPos.y = WIN_HEIGHT;
	}


	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_W))
	{
		std::cout << "W Key pressed" << std::endl;
		D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(0.0f, -200.0f, 0.0f));
	}

	if (GameInput::getInstance()->KeyboardKeyHold(DIK_A))
	{
		std::cout << "Key pressed" << std::endl;
		D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(-mov, 0.0f, 0.0f));
	}

	if (GameInput::getInstance()->KeyboardKeyHold(DIK_D))
	{
		std::cout << "Key pressed" << std::endl;
		D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(mov, 0.0f, 0.0f));
	}

	if (GameInput::getInstance()->KeyboardKeyHold(DIK_S))
	{
		std::cout << "Key pressed" << std::endl;
		D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(0.0f, mov, 0.0f));
	}

	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_Q))
	{
		GameGraphics* gGraphics = gGraphics->getInstance();
		std::cout << "Toggle Fullscreen" << std::endl;
		if (gGraphics->d3dPP.Windowed)
		{
			std::cout << "Fullscreen" << std::endl;
			gGraphics->d3dPP.Windowed = false;
			gGraphics->d3dPP.BackBufferFormat = D3DFMT_A8R8G8B8;
			sprite->OnLostDevice();
			gGraphics->d3dDevice->Reset(&gGraphics->d3dPP);
		}
		else if (!gGraphics->d3dPP.Windowed)
		{
			std::cout << "Windowed" << std::endl;
			gGraphics->d3dPP.Windowed = true;
			gGraphics->d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
			sprite->OnLostDevice();
			gGraphics->d3dDevice->Reset(&gGraphics->d3dPP);
		}
	}

	D3DXVECTOR2 rotationCentre = D3DXVECTOR2(0, 0); //(0,0) is in the centre of the sprite
	//D3DXVECTOR3 spriteCentre3D = D3DXVECTOR3(256.0f, 256.0f, 0.0f);
	// Screen position of the sprite
	D3DXVECTOR2 trans = D3DXVECTOR2(0.0f, 0.0f);
	GameInput* gInput = GameInput::getInstance();

	float angle = atan2(playerPos.y - gInput->mousePosition.y, playerPos.x - gInput->mousePosition.x);
	float angleD = (D3DXToDegree(angle) < 0 ? D3DXToDegree(angle) + 360 : D3DXToDegree(angle));

/*			90
			|
			|
			|
0/360------------------180
			|
			|
			|
			270	*/	

	std::cout << angleD << std::endl;
	D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, &rotationCentre, D3DXToRadian(angleD), &D3DXVECTOR2(playerPos.x, playerPos.y));
	
}

void Level1::fixedUpdate()
{

}

void Level1::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 spriteCentre3D = D3DXVECTOR3(256.0f, 256.0f, 0.0f);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, &spriteCentre3D, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void Level1::release()
{

}
