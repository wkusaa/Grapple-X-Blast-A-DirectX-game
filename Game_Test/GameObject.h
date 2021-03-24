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
	D3DXVECTOR3 rotation;//not sure where to use
	D3DXVECTOR3 rotationCentre;
	D3DXVECTOR3 spriteCentre;
	D3DXVECTOR3 scaling;
	D3DXVECTOR3 size;
	D3DXMATRIX mat;
	RECT spriteRect;

	bool animationLoop;
	int currentFrame;
	int animationCount;
	int animationRow;
	float animationTimer;
	float animationRate;
	float rotationAngle;

public:

	GameObject();
	~GameObject();
	virtual void Initialize(LPDIRECT3DDEVICE9 device);
	virtual void Update();
	virtual void SetTransform();
	virtual void Draw();
	void Initialize(LPDIRECT3DDEVICE9 device, LPCSTR sourceFile);

	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
	D3DXVECTOR3 direction;

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

	void setAnimationRow(int animationRow);
	int getAnimationRow();

	void setAnimationCount(int animationCount);
	int getAnimationCount();

	void setAnimationLoop(bool animationLoop);
	bool getAnimationLoop();

	void setCurrentFrame(int currentFrame);
	int getCurrentFrame();
};

