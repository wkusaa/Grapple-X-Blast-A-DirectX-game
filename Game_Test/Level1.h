#pragma once
#include "GameState.h"
#include <iostream>
#define MOSTIMA "images/mostima.png"
#define EXUSIAI "images/exusiai.png"

class Level1 :public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 playerPos;
	RECT spriteRect;
	D3DXMATRIX mat;

public:
	Level1();
	~Level1();

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

