#pragma once
#include "GameStateManager.h"
#include "GameState.h"
#define GAMEOVER "assets/GameOverScene.png"

class GameOverScene:public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;
public:
	GameOverScene();
	~GameOverScene(); 
	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

