#pragma once
#include "GameState.h"
#include "Player.h"
#include "GrapplingPoint.h"
#include "GameStateManager.h"
#include "DXLine.h"
#include <iostream>

class TestLevel3 :public GameState
{
private:
	//GameObject* player;
	GrapplingPoint* grapplePoint;
public:
	TestLevel3();
	~TestLevel3();

	float rotation = 0;
	float angleDegree = 90;
	bool swingOppositeDirection;
	D3DXVECTOR3 gravity = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	D3DXVECTOR3 direction = D3DXVECTOR3(4.0f, -2.0f, 0.0f);

	//DXLine* line;

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};
