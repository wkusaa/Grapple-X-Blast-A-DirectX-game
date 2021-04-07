#pragma once
#include "GameStateManager.h"
#include "GameState.h"
#define TUTORIAL "assets/mainScene1.png"

class TutorialScene :public GameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;
public:
	TutorialScene();
	~TutorialScene();
	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

