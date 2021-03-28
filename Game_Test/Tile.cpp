#include "Tile.h"

Brick::Brick(float x, float y, float z)
{
	std::cout << "Bricks created" << std::endl;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 32;
	spriteRect.right = 32;
	size = D3DXVECTOR3(32.0f ,32.0f ,0);
}

void Brick::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);

	D3DXCreateTextureFromFileEx(device, BRICK, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

Brick::~Brick()
{
}

//void Brick::setPosition(float x, float y, float z)
//{
//	this->position.x = x;
//	this->position.y = y;
//	this->position.z = z;
//}

void Brick::Render()
{
	D3DXVECTOR3 p = position;
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

Lava::Lava(float x, float y, float z)
{
	std::cout << "Lava created" << std::endl;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 32;
	spriteRect.right = 32;
	size = D3DXVECTOR3(32.0f, 32.0f, 0);
}

void Lava::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);

	D3DXCreateTextureFromFileEx(device, LAVA, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

Lava::~Lava()
{
}

//void Lava::setPosition(float x, float y, float z)
//{
//	this->position.x = x;
//	this->position.y = y;
//	this->position.z = z;
//}

void Lava::Render()
{
	D3DXVECTOR3 p = position;
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

Grass::Grass(float x, float y, float z)
{
	std::cout << "Grass created" << std::endl;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 32;
	spriteRect.right = 32;
	size = D3DXVECTOR3(32.0f, 32.0f, 0);
}

void Grass::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);

	D3DXCreateTextureFromFileEx(device, GRASS, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

Grass::~Grass()
{
}

//void Grass::setPosition(float x, float y, float z)
//{
//	this->position.x = x;
//	this->position.y = y;
//	this->position.z = z;
//}

void Grass::Render()
{
	D3DXVECTOR3 p = position;
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

Door::Door(float x, float y, float z)
{
	std::cout << "Door created" << std::endl;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 64;
	spriteRect.right = 64;
	size = D3DXVECTOR3(64.0f, 64.0f, 0);
}

void Door::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);

	D3DXCreateTextureFromFileEx(device, WINDOW, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

Door::~Door()
{
}

//void Window::setPosition(float x, float y, float z)
//{
//	this->position.x = x;
//	this->position.y = y;
//	this->position.z = z;
//}

void Door::Render()
{
	D3DXVECTOR3 p = position;
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

Trap::Trap(float x, float y, float z)
{
	std::cout << "Trap created" << std::endl;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 32;
	spriteRect.right = 32;
	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = 32/2;
	bounding_box.right = 32;
	size = D3DXVECTOR3(32.0f, 16.0f, 0);
}

void Trap::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);

	D3DXCreateTextureFromFileEx(device, TRAP, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

Trap::~Trap()
{
}

//void Window::setPosition(float x, float y, float z)
//{
//	this->position.x = x;
//	this->position.y = y;
//	this->position.z = z;
//}

void Trap::Render()
{
	D3DXVECTOR3 p = position;
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

