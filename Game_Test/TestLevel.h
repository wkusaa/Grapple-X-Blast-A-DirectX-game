#pragma once
#include "GameState.h"
#include <iostream>

class TestLevel :public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 playerPos;
	RECT spriteRect;
	D3DXMATRIX mat;

public:
	TestLevel();
	~TestLevel();

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

