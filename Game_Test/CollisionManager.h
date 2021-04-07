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
	//bool checkSquareCollide(Player * player, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize, int tileType, int playerAction);
	bool checkSquareCollide(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize, int tileType, int playerAction, D3DXVECTOR3 & playerVel);
	RECT relativeRect(D3DXVECTOR3 position, RECT rect, D3DXVECTOR3 centerPoint);
	bool checkMousePointCollision(RECT colliderRect);
	CollisionManager();
	~CollisionManager();
	
	bool checkCollision(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbBox, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize, int tileType, int playerAction, D3DXVECTOR3& playerVel);
	float checkCollision(Player * player, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize, float & normalx, float & normaly);
	bool collisionDetect(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize);
	//bool checkCollision(Player* player, RECT gameObjectBbSize, int tileType, int playerAction);
};

