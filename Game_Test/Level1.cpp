#include "Level1.h"

Level1::Level1()
{
	texture = NULL;
	sprite = NULL;
	playerPos = D3DXVECTOR3(0, 0, 0);
	spriteRect.left = 189;
	spriteRect.top = 196;
	spriteRect.right = 310;
	spriteRect.bottom = 320;
}

Level1::~Level1()
{
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
	D3DXCreateTextureFromFile(GameGraphics::getInstance()->d3dDevice, "mostima.png", &texture);
}

void Level1::update()
{
	D3DXVec3Add(&playerPos, &playerPos, &D3DXVECTOR3(0.5, 0.5, 0));
}

void Level1::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &playerPos, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void Level1::release()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}
