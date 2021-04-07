#pragma once
#include <algorithm>
#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include <math.h>

class CollisionManager
{
private:

public:
	RECT relativeRect(D3DXVECTOR3 position, RECT rect, D3DXVECTOR3 centerPoint);
	bool checkMousePointCollision(RECT colliderRect);
	CollisionManager();
	~CollisionManager();
	
	bool checkCollision(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbBox, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize, int tileType, int playerAction, D3DXVECTOR3& playerVel);
	float checkCollision(Player * player, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize, float & normalx, float & normaly);
	bool collisionDetect(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize);
};

