#include "Player.h"

Player* Player::instance = 0;

Player::Player()
{
	std::cout << "Player created" << std::endl;
	texture = NULL;
	sprite = NULL;

	speed = 1.0f;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	movement = D3DXVECTOR3();
	size = D3DXVECTOR3(128.0f, 128.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(WIN_WIDTH/2, WIN_HEIGHT/2, 0);
	mat = D3DMATRIX();
	rotation = D3DXVECTOR3();
	rotationAngle = 0;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	animationTimer = 0;
	animationRate = 0.5f / 8;
	currentFrame = 0;
	rotationRate = 0;

	blastCannon.setPosition(position);
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
	//sprite->Release();
	//sprite = NULL;

	//texture->Release();
	//texture = NULL; destructor called at GameObject
}

//BlastCannon Player::BlastCannon()
//{
//	return blastCannon;
//}

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
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, PLAYER_SPRITE, &texture);

	blastCannon.Initialize(device);
}

//void Player::Begin()
//{
//	sprite->Begin(D3DXSPRITE_ALPHABLEND);
//}

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

	blastCannon.Update();
	blastCannon.setPosition(position);
}

void Player::Draw()
{
	SetTransform();
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
	blastCannon.Draw();
}

void Player::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	blastCannon.Begin();
}

//void Player::SetTransform()
//{
//	D3DXMatrixTransformation2D(&mat, NULL, NULL, &D3DXVECTOR2(scaling.x, scaling.y), &D3DXVECTOR2(rotationCentre.x, rotationCentre.y), D3DXToRadian(rotationAngle), &D3DXVECTOR2(position.x, position.y));
//	sprite->SetTransform(&mat);
//}



void Player::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}