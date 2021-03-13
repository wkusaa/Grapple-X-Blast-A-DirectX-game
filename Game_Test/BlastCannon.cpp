#include "BlastCannon.h"

BlastCannon::BlastCannon()
{
	std::cout << "BlastCannon created" << std::endl;
	texture = NULL;
	sprite = NULL;


	rotationCentre = D3DXVECTOR3(0, 0, 0);

	scaling = D3DXVECTOR3(0.5f, 0.5f, 1.0f);
	size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x/2, size.y/2, 0.0f);
	position = D3DXVECTOR3(0, 0, 0);
	mat = D3DMATRIX();

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

BlastCannon::~BlastCannon()
{
	std::cout << "BlastCannon destroyed" << std::endl;
}

void BlastCannon::rotateGunBasedMouse()
{
	GameInput* gInput = GameInput::getInstance();
	float angle = atan2(position.y - gInput->mousePosition.y, position.x - gInput->mousePosition.x);
	float rotationAngle = (D3DXToDegree(angle) < 0 ? D3DXToDegree(angle) + 360 : D3DXToDegree(angle));

	rotationAngle =	rotationAngle-180;

	std::cout << rotationAngle << std::endl;
	setRotationAngle(rotationAngle);
}

void BlastCannon::Initialize(LPDIRECT3DDEVICE9 device)
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(device, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(device, BLAST_CANNON, &texture);
}

void BlastCannon::Update()
{
	rotateGunBasedMouse();
}

void BlastCannon::Draw()
{
	SetTransform();
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void BlastCannon::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

