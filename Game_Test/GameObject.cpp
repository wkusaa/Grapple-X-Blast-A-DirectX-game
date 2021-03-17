#include "GameObject.h"

GameObject::GameObject()
{
	std::cout << "GameObject created" << std::endl;

	texture = NULL;
	sprite = NULL;

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

//void GameObject::Begin()
//{
//	sprite->Begin(D3DXSPRITE_ALPHABLEND);
//}

void GameObject::SetTransform()
{
	D3DXMatrixTransformation2D(&mat, NULL, NULL, &D3DXVECTOR2(scaling.x, scaling.y), &D3DXVECTOR2(rotationCentre.x, rotationCentre.y), rotationAngle, &D3DXVECTOR2(position.x, position.y));//in rotation angle is in radian
	sprite->SetTransform(&mat);
}

void GameObject::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}


void GameObject::Initialize(LPDIRECT3DDEVICE9 device, LPCSTR sourceFile)
{
	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(device, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(device, sourceFile, &texture);
}

void GameObject::setPosition(D3DXVECTOR3 position)
{
	this->position = position;
}

void GameObject::setSize(D3DXVECTOR3 size)
{
	this->size = size;
}

D3DXVECTOR3 GameObject::getSize()
{
	return size;
}

void GameObject::setScaling(D3DXVECTOR3 scaling)
{
	this->scaling = scaling;
}

D3DXVECTOR3 GameObject::getScaling()
{
	return this->scaling;
}

void GameObject::setSpriteCentre(D3DXVECTOR3 spriteCentre)
{
	this->spriteCentre = spriteCentre;
}

D3DXVECTOR3 GameObject::getSpriteCentre()
{
	return spriteCentre;
}

void GameObject::setRotationCentre(D3DXVECTOR3 rotationCentre)
{
	this->rotationCentre = rotationCentre;
}

D3DXVECTOR3 GameObject::getRotationCentre()
{
	return this->rotationCentre;
}

void GameObject::setRotationAngle(float rotationAngle)
{
	this->rotationAngle = rotationAngle;
}

float GameObject::getRotationAngle()
{
	return this->rotationAngle;
}

D3DXVECTOR3 GameObject::getPosition()
{
	return this->position;
}

void GameObject::setMatrix(D3DXMATRIX matrix)
{
	this->mat = matrix;
}

D3DXMATRIX GameObject::getMatrix()
{
	return mat;
}
