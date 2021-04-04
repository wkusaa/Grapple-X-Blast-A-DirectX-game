#include "Ammo.h"

Ammo::Ammo()
{
	std::cout << "Ammo created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(16.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 16;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 1.0f / animationCount;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

}

Ammo::Ammo(D3DXVECTOR3 position)
{
	std::cout << "Ammo created" << std::endl;
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	size = D3DXVECTOR3(16.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 8;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.5f / animationCount*animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

Ammo::~Ammo()
{
	std::cout << "Ammo destroyed" << std::endl;
}

void Ammo::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, AMMO, &texture);
}

void Ammo::Update()
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
		if (currentFrame == 0)
		{
			animationRow++;
			animationRow %= animationCountCol;
		}
	}

	spriteRect.top = size.y * animationRow;
	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

AmmoUI::AmmoUI()
{
	
}

AmmoUI::AmmoUI(D3DXVECTOR3 position)
{
	texture = NULL;
	sprite = NULL;
	font = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32.0f, 32.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

AmmoUI::~AmmoUI()
{
	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void AmmoUI::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, BULLETUI, &texture);

	D3DXCreateFont(device, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	textRect.left = 24;
	textRect.top = -10;
	textRect.right = 48;
	textRect.bottom = 16;
}

void AmmoUI::Update()
{
}

void AmmoUI::render()
{
	std::string strAmmoAmount = std::to_string(Player::getInstance()->getAmmoAmount());
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(sprite, strAmmoAmount.c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(65, 8, 252));
	sprite->End();
}

