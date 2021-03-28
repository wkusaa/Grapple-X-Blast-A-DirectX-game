#include "Crosshair.h"

Crosshair::Crosshair()
{
	std::cout << "Crosshair created" << std::endl;
	texture = NULL;
	sprite = NULL;
	rotationCentre = D3DXVECTOR3(0, 0, 0);

	scaling = D3DXVECTOR3(0.03f, 0.03f, 1.0f);
	size = D3DXVECTOR3(1024.0f, 1024.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0, 0, 0);
	mat = D3DMATRIX();

	bounding_box.top = 0;
	bounding_box.left = 0;
	bounding_box.bottom = bounding_box.top + size.y;
	bounding_box.right = bounding_box.left + size.x;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

Crosshair::~Crosshair()
{
	std::cout << "Crosshair destroyed" << std::endl;
}

void Crosshair::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, CROSSHAIR, &texture);
}

void Crosshair::Update()
{
	GameInput* gameInput = GameInput::getInstance();

	position.x = gameInput->mousePosition.x;
	position.y = gameInput->mousePosition.y;
}
