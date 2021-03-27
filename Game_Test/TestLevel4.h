#pragma once
#include "GameState.h"
#include "Player.h"
#include "PlayerController.h"
#include <vector>
#include "GrapplingPoint.h"
#include "Key.h"
#include "Ammo.h"
#include "Gems.h"
#include <iostream>

class TestLevel4 :public GameState
{
private:
	PlayerController* playerCon;
	std::vector<GrapplingPoint*> grapplePointArray;
	Key* key1;
	std::vector<Ammo*> ammoArray;
	std::vector<Gems*> gemsArray;
public:
	TestLevel4();
	~TestLevel4();

	float rotation = 0;
	D3DXVECTOR3 gravity = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	//DXLine* line;

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
};
