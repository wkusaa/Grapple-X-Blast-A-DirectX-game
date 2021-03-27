#include "Explosion.h"

Explosion::Explosion()
{
	std::cout << "Explosion created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount*animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = false;
	animationComplete = false;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

}

Explosion::Explosion(D3DXVECTOR3 position)
{
	std::cout << "Explosion created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = false;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

Explosion::~Explosion()
{
	std::cout << "Explosion destroyed" << std::endl;
}

void Explosion::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, EXPLOSION, &texture);
}

void Explosion::Update()
{
	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationRate)
	{
		animationTimer -= animationRate;
		currentFrame++;
		if (animationLoop)
		{
			currentFrame %= animationCount;
			if (currentFrame == 0)
			{
				animationRow++;
				animationRow %= animationCountCol;
			}
		}
		else
		{
			if (currentFrame == animationCount)
			{
				animationRow++;
				currentFrame = 0;

				if (animationRow >= animationCountCol)
				{
					animationRow = animationCountCol;
				}
			}
			if (currentFrame >= animationCount - 1)
			{
				currentFrame = animationCount - 1;
			}
		}

	}

	spriteRect.top = size.y * animationRow;
	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}
