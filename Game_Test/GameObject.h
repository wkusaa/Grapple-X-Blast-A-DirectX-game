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
	D3DXVECTOR3 position;
	D3DXVECTOR3 movement;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXVECTOR3 size;
	D3DXMATRIX mat;
	RECT spriteRect;


	int currentFrame;
	float animationTimer;
	float animationRate;
	float rotationRate;

public:
	GameObject();
	~GameObject();
	D3DXVECTOR3 GetPosition();
	virtual void Initialize(LPDIRECT3DDEVICE9 device);
	virtual void Update();
	virtual void Begin();
	virtual void SetTransform(D3DXMATRIX mat);
	virtual void Draw();
	virtual void ReleaseInstance();
	void Initialize(LPDIRECT3DDEVICE9 device, LPCSTR sourceFile);
};

