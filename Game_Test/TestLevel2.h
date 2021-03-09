#pragma once
#include "GameState.h"
#include "Player.h"
#include <iostream>

class TestLevel2 :public GameState
{
private:
	//GameObject* player;
public:
	TestLevel2();
	~TestLevel2();

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};

