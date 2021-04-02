#pragma once
#include "GameObject.h"
#include "Player.h"

class CollisionManager
{
private:

public:
	bool checkCollision(D3DXVECTOR3 pos1, RECT rect1, D3DXVECTOR3 pos2, RECT rect2);
	int checkSideCollide(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 object, D3DXVECTOR3 objectSize);
	CollisionManager();
	~CollisionManager();
};

