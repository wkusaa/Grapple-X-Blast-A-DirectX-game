#pragma once
#include <algorithm>
#include <iostream>
#include "GameObject.h"
#include "Player.h"

class CollisionManager
{
private:

public:
	//bool checkCollision(D3DXVECTOR3 pos1, RECT rect1, D3DXVECTOR3 pos2, RECT rect2, float& normalx, float& normaly);
	int checkSideCollide(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 object, D3DXVECTOR3 objectSize);
	RECT relativeRect(D3DXVECTOR3 position, RECT rect, D3DXVECTOR3 centerPoint);
	bool checkMousePointCollision(RECT colliderRect);
	CollisionManager();
	~CollisionManager();
	bool checkCollision(Player* player, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize, int tileType);
};

