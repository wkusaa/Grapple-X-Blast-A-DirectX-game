#pragma once
#include "GameState.h"
#include "Player.h"
#include <iostream>
#define PLAYER_RUN "assets/player/run/Run_Spritesheet.png"
#define PLAYER_SPRITE "assets/player/player_spritesheet.png"

class TestLevel :public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 playerPos;
	RECT spriteRect;
	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre2D;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 size;
	D3DXVECTOR3 spriteCentre3D;
	float rotation;
	int currentFrame;
	float animationTimer;
	float animationRate;


public:
	TestLevel();
	~TestLevel();

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

