#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>


class GameObject
{
private:

protected:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 movement;
	D3DXVECTOR3 rotation;//not sure where to use
	D3DXVECTOR3 rotationCentre;
	D3DXVECTOR3 spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXVECTOR3 size;
	D3DXMATRIX mat;
	RECT spriteRect;

	int currentFrame;
	float animationTimer;
	float animationRate;
	float rotationRate;
	float rotationAngle;

public:
	GameObject();
	~GameObject();
	virtual void Initialize(LPDIRECT3DDEVICE9 device);
	virtual void Update();
	//virtual void Begin();
	virtual void SetTransform();
	virtual void Draw();
	void Initialize(LPDIRECT3DDEVICE9 device, LPCSTR sourceFile);

	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;

	void setPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 getPosition();

	void setMatrix(D3DXMATRIX matrix);
	D3DXMATRIX getMatrix();

	void setSize(D3DXVECTOR3 size);
	D3DXVECTOR3 getSize();

	void setScaling(D3DXVECTOR3 scaling);
	D3DXVECTOR3 getScaling();

	void setSpriteCentre(D3DXVECTOR3 spriteCentre);
	D3DXVECTOR3 getSpriteCentre();

	void setRotationCentre(D3DXVECTOR3 rotationCentre);
	D3DXVECTOR3 getRotationCentre();

	void setRotationAngle(float rotationAngle);
	float getRotationAngle();
};

