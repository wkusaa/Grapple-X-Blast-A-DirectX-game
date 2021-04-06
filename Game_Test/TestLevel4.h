#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Player.h"
#include "PlayerController.h"
#include <vector>
#include "GrapplingPoint.h"
#include "Key.h"
#include "Ammo.h"
#include "Gems.h"
#include "Tile.h"
#include "Gate.h"
#include "CollisionManager.h"
#include "GameSound.h"
#include <iostream>

class TestLevel4 : public GameState
{
private:
	PlayerController* playerCon;
	std::vector<GrapplingPoint*> grapplePointArray;
	
	std::vector<Ammo> ammoArray;
	std::vector<Gems> gemsArray;
	std::vector<Key> keysArray;
	std::vector<Platform*> platformArray;
	std::vector<Spike*> spikeArray;
	std::vector<Brazier*> brazierArray;
	CollisionManager* collision;
	Gate* gate;
	KeyUI* keyUI;
	AmmoUI* ammoUI;

public:
	TestLevel4();
	~TestLevel4();

	void init();
	void update(); 
	void fixedUpdate();
	void draw();
	void release();
	void buildLevel();
	void loadScene();
	void nextScene();
	void GameOver();
	void restartLevel();
	void releaseLevel();
};
