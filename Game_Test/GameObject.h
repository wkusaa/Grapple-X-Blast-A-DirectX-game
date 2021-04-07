#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>

//typedef GameObject * GAMEOBJECT;

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
	D3DXVECTOR3 size;
	D3DXVECTOR3 bbSize;
	D3DXMATRIX mat;
	RECT bounding_box;
	LPD3DXFONT font;
	RECT textRect;
	RECT collderBox;


	bool animationComplete;
	bool animationLoop;
	int objectType;
	int currentFrame;
	int animationCount;
	int animationRow;
	int animationCountCol;
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

	RECT spriteRect;
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
	D3DXVECTOR3 direction;
	D3DXVECTOR3 scaling;

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

	RECT getBounding_Box();
	D3DXVECTOR3 getBbBoxSize() { return bbSize; };
	void setColliderBox(float top, float bottom, float left, float right); 
	RECT getColliderBox() { return collderBox; };
	void setObjectType(int i) { this->objectType = i; }; //1 = standing platform
	int getObjectType() { return objectType; };
};

