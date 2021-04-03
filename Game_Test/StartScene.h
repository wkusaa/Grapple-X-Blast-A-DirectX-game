#pragma once
#include "GameStateManager.h"
#include "GameState.h"
#define STARTSCENE "assets/mainScene.png"

class StartScene:public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;
public:
	StartScene();
	~StartScene();
	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

