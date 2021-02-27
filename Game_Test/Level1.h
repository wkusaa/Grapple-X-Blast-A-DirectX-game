#pragma once
#include "GameState.h"
#include <iostream>
class Level1 :public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 playerPos;
	RECT spriteRect;

public:
	Level1();
	~Level1();

	void init();
	void update();
	void draw();
	void release();
};

