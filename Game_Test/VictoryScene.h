#pragma once
#include "GameStateManager.h"
#include "GameState.h"
#define VICTORY "assets/victory.png"

class VictoryScene:public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;

	GameSound* victorySound;

public:
	VictoryScene();
	~VictoryScene();
	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	void loadScene();
};

