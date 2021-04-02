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

	D3DXVECTOR3 objectCenter;
	objectCenter.x = (rect2.right - rect2.left) / 2;
	objectCenter.y = (rect2.bottom - rect2.top) / 2;
	rect2.right = pos2.x + rect2.right - rect2.left - objectCenter.x;
	rect2.left = pos2.x - objectCenter.x;
	rect2.bottom = pos2.y + rect2.bottom - rect2.top - objectCenter.y;
	rect2.top = pos2.y - objectCenter.y;

	if (rect1.bottom < rect2.top) return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;
	
	return true;
}

int CollisionManager::checkSideCollide(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 object, D3DXVECTOR3 objectSize)
{
	Player* player = Player::getInstance();
	float player_bottom = playerPos.y + (playerBbSize.y/2);
	float tiles_bottom = object.y + (objectSize.y/2);
	float player_right = playerPos.x + (playerBbSize.x/2);
	float tiles_right = object.x + (objectSize.x/2);

	float b_collision = tiles_bottom - playerPos.y - (playerBbSize.y / 2);
	float t_collision = player_bottom - object.y - (objectSize.y / 2);
	float l_collision = player_right - object.x - (objectSize.x / 2);
	float r_collision = tiles_right - playerPos.x - (playerBbSize.x / 2);

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
	{
		player->position -= (player->velocity);
		//player->isMoving = false;
		return 1;
		//Top collision
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
	{
		player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
		player->position += (player->velocity);
		player->isMoving = true;
		return 2;
		//bottom collision
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
		player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
		player->position += (player->velocity);
		player->isMoving = false;
		return 3;
		//Left collision
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
	{
		player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
		player->position += (player->velocity);
		player->isMoving = true;
		return 4;
		//Right collision
	}
	return 0;
}

RECT CollisionManager::relativeRect(D3DXVECTOR3 position, RECT rect, D3DXVECTOR3 centerPoint)
{
	rect.right = position.x + rect.right - rect.left - centerPoint.x;
	rect.left = position.x - centerPoint.x;
	rect.bottom = position.y + rect.bottom - rect.top - centerPoint.y;
	rect.top = position.y - centerPoint.y;

	return rect;
}

bool CollisionManager::checkMousePointCollision(RECT colliderRect)
{
	GameInput* gameInput = GameInput::getInstance();

	if (colliderRect.bottom < gameInput->mousePosition.y) return false;

	if (colliderRect.top > gameInput->mousePosition.y) return false;

	if (colliderRect.right < gameInput->mousePosition.x) return false;

	if (colliderRect.left > gameInput->mousePosition.x) return false;

	//std::cout << "Collide" << std::endl;

	return true;
}



CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
}




