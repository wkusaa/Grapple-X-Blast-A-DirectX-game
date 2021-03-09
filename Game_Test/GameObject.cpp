#include "GameObject.h"

GameObject::GameObject()
{
	std::cout << "GameObject created" << std::endl;

	//texture = NULL;
	//sprite = NULL;

	//scaling = D3DXVECTOR3();
	//movement = D3DXVECTOR3();
	//spriteCentre = D3DXVECTOR3();
	//size = D3DXVECTOR3();
	//position = D3DXVECTOR3();
	//rotation = D3DXVECTOR3();
	//mat = D3DMATRIX();

	//spriteRect.top = 0;
	//spriteRect.left = 0;
	//spriteRect.bottom = 0;
	//spriteRect.right = 0;

	//animationTimer = 0;
	//animationRate = 0;
	//currentFrame = 0;
	//rotationRate = 0;
}

GameObject::~GameObject()
{
	std::cout << "GameObject destroyed" << std::endl;
	//sprite->Release();
	//sprite = NULL;

	//texture->Release();
	//texture = NULL;

}

D3DXVECTOR3 GameObject::GetPosition()
{
	return position;
}

void GameObject::Initialize(LPDIRECT3DDEVICE9 device)
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(device, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(device, "", &texture);
}

void GameObject::Update()
{

}

void GameObject::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GameObject::SetTransform(D3DXMATRIX mat)
{
	sprite->SetTransform(&mat);
}

void GameObject::Draw()
{
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void GameObject::ReleaseInstance()
{

}

void GameObject::Initialize(LPDIRECT3DDEVICE9 device, LPCSTR sourceFile)
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(device, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(device, sourceFile, &texture);
}
