#include "GrapplingPoint.h"

GrapplingPoint::GrapplingPoint()
{
	std::cout << "Grappling Point created" << std::endl;
	texture = NULL;
	sprite = NULL;
	rotationCentre = D3DXVECTOR3(0, 0, 0);

	scaling = D3DXVECTOR3(0.5f, 0.5f, 1.0f);
	size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0, 0, 0);
	mat = D3DMATRIX();

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

GrapplingPoint::GrapplingPoint(D3DXVECTOR3 position)
{
	std::cout << "Grappling Point created at position" << std::endl;
	texture = NULL;
	sprite = NULL;
	rotationCentre = D3DXVECTOR3(0, 0, 0);

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(16.0f, 16.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

GrapplingPoint::~GrapplingPoint()
{
	std::cout << "Grappling Point destroyed" << std::endl;
}

void GrapplingPoint::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, GRAPPLING_POINT, &texture);
}
