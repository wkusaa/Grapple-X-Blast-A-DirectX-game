#include "Player.h"

Player* Player::instance = 0;

Player::Player()
{
	std::cout << "Player created" << std::endl;
	texture = NULL;
	sprite = NULL;

	speed = 1.0f;

	scaling = D3DXVECTOR3(3.0f, 3.0f, 1.0f);
	size = D3DXVECTOR3(128.0f, 128.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(WIN_WIDTH/2, WIN_HEIGHT/2, 0);
	mat = D3DMATRIX();
	rotation = D3DXVECTOR3();
	velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotationAngle = 0;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	animationTimer = 0;
	animationRate = 0.5f / 8;
	currentFrame = 0;
	rotationRate = 0;

	//blastCannon.setPosition(position);
	blastCannon = new BlastCannon; // true = blastCannon
	grappleGun = new GrappleGun; // false = grappleGun

	blastCannon->Initialize(GameGraphics::getInstance()->d3dDevice);
	grappleGun->Initialize(GameGraphics::getInstance()->d3dDevice);


}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
	delete blastCannon;
	delete grappleGun;
	currentWeapon = NULL;
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

	currentWeapon->Update();
	currentWeapon->setPosition(position);
}

void Player::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
	currentWeapon->Draw();
}


void Player::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}

float Player::getBlastOffAngle()
{
	float mousePointAngle;
	mousePointAngle = currentWeapon->getRotationAngle() - D3DXToRadian(90); //offset by 90 degrees
	float blastOffAngle = mousePointAngle;

	return blastOffAngle;
}

//void Player::switchWeapon()
//{
//	if (isSwitched)
//	{
//		currentWeapon = grappleGun;
//		isSwitched = false;
//	}
//	else
//	{
//		currentWeapon = blastCannon;
//		isSwitched = true;
//	}
//}
//
//void Player::action()
//{
//	if (isSwitched)
//	{
//		//std::cout << blastCannon->position.x << std::endl;
//
//	}
//	else
//	{
//
//	}
//}