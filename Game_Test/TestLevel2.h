#pragma once
#include "GameState.h"
#include "Player.h"
#include "GameStateManager.h"
#include <iostream>

class TestLevel2 :public GameState
{
private:
	//GameObject* player;
public:
	TestLevel2();
	~TestLevel2();

	float rotation = 0;
	D3DXVECTOR3 gravity = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	D3DXVECTOR3 direction = D3DXVECTOR3(4.0f, -2.0f, 0.0f);

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

