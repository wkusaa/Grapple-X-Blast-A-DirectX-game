#include "CollisionManager.h"

bool CollisionManager::checkCollision(D3DXVECTOR3 pos1, RECT rect1, D3DXVECTOR3 pos2, RECT rect2)
{
	D3DXVECTOR3 characterCenter;

	characterCenter.x = (rect1.right - rect1.left) / 2;
	characterCenter.y = (rect1.bottom - rect1.top) / 2;
	rect1.right = pos1.x + rect1.right - rect1.left - characterCenter.x;
	rect1.left = pos1.x - characterCenter.x;
	rect1.bottom = pos1.y + rect1.bottom - rect1.top - characterCenter.y;
	rect1.top = pos1.y - characterCenter.y;

	rect2.right = pos2.x + rect2.right - rect2.left;
	rect2.left = pos2.x;
	rect2.bottom = pos2.y + rect2.bottom - rect2.top;
	rect2.top = pos2.y;

	if (rect1.bottom < rect2.top) return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;

	return true;
}

int CollisionManager::checkSideCollide(D3DXVECTOR3 player, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 object, D3DXVECTOR3 objectSize)
{
	float player_bottom = player.y + (playerBbSize.y/2); 
	float tiles_bottom = object.y + objectSize.y;
	float player_right = player.x + (playerBbSize.x/2);
	float tiles_right = object.x + objectSize.x;

	float b_collision = tiles_bottom - player.y - 18;
	float t_collision = player_bottom - object.y;
	float l_collision = player_right - object.x;
	float r_collision = tiles_right - player.x - 11;

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
	{
		return 2;
		//Top collision
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
	{
		return 3;
		//bottom collision
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
		return 4;
		//Left collision
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
	{
		return 1;
		//Right collision
	}

	return 0;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
