#include "Gems.h"

Gems::Gems()
{
	std::cout << "Gems created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(16.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 16;
	animationTimer = 0;
	animationRate = 1.0f / animationCount;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
	objectType = 2;
}

Gems::Gems(D3DXVECTOR3 position)
{
	std::cout << "Gems created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(16.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();

	animationCount = 16;
	animationTimer = 0;
	animationRate = 1.0f / animationCount;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
	objectType = 2;
}

Gems::~Gems()
{
	std::cout << "Gems destroyed" << std::endl;
}

void Gems::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, GEMS, &texture);
}

void Gems::Update()
{
	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationRate)
	{
		animationTimer -= animationRate;
		currentFrame++;
		if (animationLoop)
		{
			currentFrame %= animationCount;
		}
	}

	spriteRect.top = size.y * animationRow;
	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}
