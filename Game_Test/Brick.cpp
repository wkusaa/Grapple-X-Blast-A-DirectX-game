#include "Brick.h"

Brick::Brick()
{
	/*spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = 64;
	spriteRect.right = 64;*/
}

void Brick::Initialize(LPDIRECT3DDEVICE9 device)
{
	
}

Brick::~Brick()
{
}

void Brick::Draw(float x, float y, float z)
{
	D3DXVECTOR3 p(x, y, z);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}
