#pragma once
#include "Player.h"
class PlayerController
{
private:
	Player* player;

public:
	PlayerController();
	~PlayerController();

	void Update();
};

