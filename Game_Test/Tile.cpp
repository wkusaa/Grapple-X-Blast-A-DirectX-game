#include "Tile.h"

Brick::Brick(float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;

}

void Brick::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, BRICK, &texture);
}

Brick::~Brick()
{
}

Lava::Lava(float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

void Lava::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, LAVA, &texture);
}

Lava::~Lava()
{
}

Grass::Grass(float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

void Grass::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, GRASS, &texture);
}

Grass::~Grass()
{
}

Door::Door(float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(64.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

void Door::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, WINDOW, &texture);
}

Door::~Door()
{
}

Trap::Trap(float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = (bounding_box.top + size.y)/2;
	bounding_box.right = bounding_box.left + size.x;
}

void Trap::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, TRAP, &texture);
}

Trap::~Trap()
{
}

Platform::Platform()
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0, 0, 0);

	platformType = 0;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;

}

Platform::Platform(int platformType)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->platformType = platformType;

	switch (platformType)
	{
	case 1:
		size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
		break;
	case 2:
		size = D3DXVECTOR3(64.0f, 32.0f, 1.0f);
		break;
	case 3:
		size = D3DXVECTOR3(128.0f, 32.0f, 1.0f);
		break;
	case 4:
		size = D3DXVECTOR3(64.0f, 256.0f, 1.0f);
		break;
	case 5:
		size = D3DXVECTOR3(64.0f, 64.0f, 1.0f);
		break;
	default:
		size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	}

	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

Platform::Platform(int platformType, float x, float y, float z)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	this->platformType = platformType;

	switch (platformType)
	{
	case 1:
		size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
		break;
	case 2:
		size = D3DXVECTOR3(64.0f, 32.0f, 1.0f);
		break;
	case 3:
		size = D3DXVECTOR3(128.0f, 32.0f, 1.0f);
		break;
	case 4:
		size = D3DXVECTOR3(64.0f, 256.0f, 1.0f);
		break;
	case 5:
		size = D3DXVECTOR3(64.0f, 64.0f, 1.0f);
		break;
	default:
		size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	}

	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}


Platform::~Platform()
{

}

void Platform::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	switch (platformType)
	{
	case 1:
		D3DXCreateTextureFromFile(device, PLATFORM1, &texture);
		break;
	case 2:
		D3DXCreateTextureFromFile(device, PLATFORM2, &texture);
		break;
	case 3:
		D3DXCreateTextureFromFile(device, PLATFORM3, &texture);
		break;
	case 4:
		D3DXCreateTextureFromFile(device, PLATFORM4, &texture);
		break;
	case 5:
		D3DXCreateTextureFromFile(device, PLATFORM5, &texture);
		break;
	default:
		D3DXCreateTextureFromFile(device, PLATFORM1, &texture);
	}
}

Spike::Spike()
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

Spike::Spike(D3DXVECTOR3 position)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

Spike::~Spike()
{

}

void Spike::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, SPIKE, &texture);
}

void Spike::Update()
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

Brazier::Brazier()
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(64.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

Brazier::Brazier(D3DXVECTOR3 position)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(64.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;
}

Brazier::~Brazier()
{

}

void Brazier::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, BRAZIER, &texture);
}

void Brazier::Update()
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