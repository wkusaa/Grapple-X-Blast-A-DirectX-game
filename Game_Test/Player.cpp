#include "Player.h"

Player* Player::instance = 0;

Player::Player()
{
	std::cout << "Player created" << std::endl;
	texture = NULL;
	sprite = NULL;

	speed = 1.0f;

	scaling = D3DXVECTOR3(5.0f, 5.0f, 1.0f);
	movement = D3DXVECTOR3();
	spriteCentre = D3DXVECTOR3(256.0f, 256.0f, 0.0f);
	size = D3DXVECTOR3(128.0f, 128.0f, 1.0f);
	position = D3DXVECTOR3(0, 0, 0);
	mat = D3DMATRIX();
	rotation = D3DXVECTOR3();

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.x;
	spriteRect.right = spriteRect.left + size.y;

	animationTimer = 0;
	animationRate = 0.5f / 8;
	currentFrame = 0;
	rotationRate = 0;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

Player* Player::getInstance()
{
	if (!instance)
	{
		instance = new Player;
	}

	return instance;
}

void Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(device, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(device, PLAYER_SPRITE, &texture);
}

void Player::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Player::Update()
{
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

void Player::SetTransform(D3DXMATRIX mat)
{
	sprite->SetTransform(&mat);
}

void Player::Draw()
{
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void Player::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}