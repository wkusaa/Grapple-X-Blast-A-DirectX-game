#include "CollisionManager.h"

//bool CollisionManager::checkCollision(D3DXVECTOR3 pos1, RECT rect1, D3DXVECTOR3 pos2, RECT rect2)
//{
//	D3DXVECTOR3 characterCenter;
//
//	characterCenter.x = (rect1.right - rect1.left) / 2;
//	characterCenter.y = (rect1.bottom - rect1.top) / 2;
//	rect1.right = pos1.x + rect1.right - rect1.left - characterCenter.x;
//	rect1.left = pos1.x - characterCenter.x;
//	rect1.bottom = pos1.y + rect1.bottom - rect1.top - characterCenter.y;
//	rect1.top = pos1.y - characterCenter.y;
//
//	D3DXVECTOR3 objectCenter;
//	objectCenter.x = (rect2.right - rect2.left) / 2;
//	objectCenter.y = (rect2.bottom - rect2.top) / 2;
//	rect2.right = pos2.x + rect2.right - rect2.left - objectCenter.x;
//	rect2.left = pos2.x - objectCenter.x;
//	rect2.bottom = pos2.y + rect2.bottom - rect2.top - objectCenter.y;
//	rect2.top = pos2.y - objectCenter.y;
//
//	if (rect1.bottom < rect2.top) return false;
//	if (rect1.top > rect2.bottom) return false;
//	if (rect1.right < rect2.left) return false;
//	if (rect1.left > rect2.right) return false;
//	
//	return true;
//}

//int CollisionManager::checkSideCollide(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 object, D3DXVECTOR3 objectSize)
//{
//	Player* player = Player::getInstance();
//	float player_bottom = playerPos.y + (playerBbSize.y/2);
//	float tiles_bottom = object.y + (objectSize.y/2);
//	float player_right = playerPos.x + (playerBbSize.x/2);
//	float tiles_right = object.x + (objectSize.x/2);
//
//	float b_collision = tiles_bottom - playerPos.y - (playerBbSize.y / 2);
//	float t_collision = player_bottom - object.y - (objectSize.y / 2);
//	float l_collision = player_right - object.x - (objectSize.x / 2);
//	float r_collision = tiles_right - playerPos.x - (playerBbSize.x / 2);
//
//	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
//	{
//		player->position -= (player->velocity);
//		//player->isMoving = false;
//		return 1;
//		//Top collision
//	}
//	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
//	{
//		player->velocity = D3DXVECTOR3(0.0f, 7.0f, 0);
//		player->position += (player->velocity);
//		player->isMoving = true;
//		return 2;
//		//bottom collision
//	}
//	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
//	{
//		player->velocity = D3DXVECTOR3(-7.0f, 0.0f, 0);
//		player->position += (player->velocity);
//		player->isMoving = false;
//		return 3;
//		//Left collision
//	}
//	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
//	{
//		player->velocity = D3DXVECTOR3(7.0f, 0.0f, 0);
//		player->position += (player->velocity);
//		player->isMoving = true;
//		return 4;
//		//Right collision
//	}
//	return 0;
//}

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


//float CollisionManager::checkCollision(Player* player, GameObject* gameObject, float& normalx, float& normaly)
//{
//	float xInvEntry, xInvExit;
//	float yInvEntry, yInvExit;
//
//	if (player->velocity.x > 0.0f)
//	{
//		xInvEntry = (gameObject->position.x - gameObject->getBounding_Box().right/2) - (player->position.x + player->getPlayerBbSize().x/2);
//		xInvExit = (gameObject->position.x + gameObject->getBounding_Box().right/2) - (player->position.x - player->getPlayerBbSize().x / 2);
//	}
//	else if (player->velocity.x < 0.0f)
//	{
//		xInvEntry = (gameObject->position.x + gameObject->getBounding_Box().right / 2) - (player->position.x - player->getPlayerBbSize().x / 2);
//		xInvExit = (gameObject->position.x - gameObject->getBounding_Box().right / 2) - (player->position.x + player->getPlayerBbSize().x / 2);
//	}
//
//	if (player->velocity.y > 0.0f)
//	{
//		yInvEntry = (gameObject->position.y - (gameObject->getBounding_Box().bottom / 2)) - (player->position.y + (player->getPlayerBbSize().y / 2));
//		yInvExit = (gameObject->position.y + (gameObject->getBounding_Box().bottom / 2)) - (player->position.y - (player->getPlayerBbSize().y / 2));
//
//	}
//	else if (player->velocity.y< 0.0f)
//	{
//		yInvEntry = (gameObject->position.y + gameObject->getBounding_Box().bottom / 2) - (player->position.y - player->getPlayerBbSize().y / 2);
//		yInvExit = (gameObject->position.y - gameObject->getBounding_Box().bottom / 2) - (player->position.y + player->getPlayerBbSize().y / 2);
//	}
//
//	float xEntry, xExit;
//	float yEntry, yExit;
//
//	if (player->velocity.x == 0.0f)
//	{
//		xEntry = -99999999999;
//		xExit = 99999999999;
//	}
//	else
//	{
//		xEntry = xInvEntry / player->velocity.x;
//		xExit = xInvExit / player->velocity.x;
//	}
//
//	if (player->velocity.y == 0.0f)
//	{
//		yEntry = -99999999999;
//		yExit = 99999999999;
//	}
//	else
//	{
//		yEntry = yInvEntry / player->velocity.y;
//		yExit = yInvExit / player->velocity.y;
//	}
//
//	float entryTime = max(xEntry, yEntry);
//	float exitTime = min(xExit, yExit);
//
//	// if there was no collision
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else // if there was a collision 
//	{
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry < 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		} 
//	}
//
//	return entryTime;
//
//
//}

bool CollisionManager::checkCollision(Player* player, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize, int tileType, int playerAction)
{
	//calculate distance between center of bounding box and center of object 
	float w = 0.5 * (player->getBbBoxSize().x + gameObjectBbSize.right);
	float h = 0.5 * (player->getBbBoxSize().y + gameObjectBbSize.bottom);

	//calculate distance between position of player and object
	float dx =  player->position.x - gameObjectPos.x;
	float dy =  player->position.y - gameObjectPos.y;

	if (playerAction == 3) return false;//swinging action no collision
	if (playerAction == 2) return false;//player dead

	if (abs(dx) <= w && abs(dy) <= h)
	{
		if (tileType == 2) return true;//for collectible items
		/* collision! */
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				player->velocity.y = -player->velocity.y;
				printf("bottom\n");
				/* collision at the bottom */
			}
			else
			{
				player->velocity.x = -player->velocity.x;
				printf("left\n");
				/* on the left */
			}
		}			
		else
		{
			if (wy > -hx)
			{
				player->velocity.x = -player->velocity.x;
				printf("right\n");/* on the right */
			}
			else
			{
				player->velocity.y = -player->velocity.y;
				printf("top\n");/* at the top */

				if (tileType == 1)//floor, so can stand on it
				{
					player->isMoving = false;
				}
				
			}
		}

		
		return true;
	}
	return false;
}

//float CollisionManager::checkCollision(Player* player, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize, float& normalx, float& normaly /*D3DXVECTOR3& contactPoint*/)
//{
//	float xInvEntry = 0, xInvExit = 0;
//	float yInvEntry = 0, yInvExit = 0;
//
//	if (player->velocity.x > 0.0f)
//	{
//		xInvEntry = (gameObjectPos.x - gameObjectBbSize.right / 2) - (player->position.x + player->getBbBoxSize().x / 2);
//		xInvExit = (gameObjectPos.x + gameObjectBbSize.right / 2) - (player->position.x - player->getBbBoxSize().x / 2);
//	}
//	else if (player->velocity.x < 0.0f)
//	{
//		xInvEntry = (gameObjectPos.x + gameObjectBbSize.right / 2) - (player->position.x - player->getBbBoxSize().x / 2);
//		xInvExit = (gameObjectPos.x - gameObjectBbSize.right / 2) - (player->position.x + player->getBbBoxSize().x / 2);
//	}
//
//	if (player->velocity.y > 0.0f)
//	{
//		yInvEntry = (gameObjectPos.y - (gameObjectBbSize.bottom / 2)) - (player->position.y + player->getBbBoxSize().y / 2);
//		yInvExit = (gameObjectPos.y + (gameObjectBbSize.bottom / 2)) - (player->position.y - player->getBbBoxSize().y / 2);
//
//	}
//	else if (player->velocity.y < 0.0f)
//	{
//		yInvEntry = (gameObjectPos.y + gameObjectBbSize.bottom / 2) - (player->position.y - player->getBbBoxSize().y / 2);
//		yInvExit = (gameObjectPos.y - gameObjectBbSize.bottom / 2) - (player->position.y + player->getBbBoxSize().y / 2);
//	}
//
//	float xEntry, xExit;
//	float yEntry, yExit;
//	printf("%f     %f     %f      %f\n", player->velocity.x, player->velocity.y, xInvEntry, yInvEntry);
//	if (player->velocity.x == 0.0f)
//	{
//		xEntry = -99999999999;
//		xExit = 99999999999;
//	}
//	else
//	{
//		xEntry = xInvEntry / player->velocity.x;
//		xExit = xInvExit / player->velocity.x;
//	}
//
//	if (player->velocity.y == 0.0f)
//	{
//		yEntry = -99999999999;
//		yExit = 99999999999;
//	}
//	else
//	{
//		yEntry = yInvEntry / player->velocity.y;
//		yExit = yInvExit / player->velocity.y;
//	}
//
//	if (xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) return 1.0f;
//
//	float entryTime = max(xEntry, yEntry);
//	float exitTime = min(xExit, yExit);
//	//contactPoint = entryTime * player->position;
//	//printf("%f     %f\n", entryTime, exitTime);
//	printf("%f     %f\n", xEntry, yEntry);
//	// if there was no collision
//	if (entryTime > exitTime)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else // if there was a collision 
//	{
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry < 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		} 
//	}
//
//	return entryTime;
//}

bool CollisionManager::collisionDetect(Player * player, D3DXVECTOR3 gameObjectPos, RECT gameObjectBbSize)
{
	float characterCenterX = player->getBbBoxSize().x / 2;
	float characterCenterY = player->getBbBoxSize().y / 2;
	float playerRight = player->position.x + characterCenterX;
	float playerLeft = player->position.x - characterCenterX;
	float playerBottom = player->position.y + characterCenterY;
	float playerTop = player->position.y - characterCenterY;
	
	float objectCenterX = gameObjectBbSize.right / 2;
	float objectCenterY = gameObjectBbSize.bottom / 2;
	float objectRight = gameObjectPos.x + objectCenterX;
	float objectLeft = gameObjectPos.x - objectCenterX;
	float objectBottom = gameObjectPos.y + objectCenterY;
	float objectTop = gameObjectPos.y - objectCenterY;
	
	if (playerBottom < objectTop) return false;
	if (playerTop > objectBottom) return false;
	if (playerRight < objectLeft) return false;
	if (playerLeft > objectRight) return false;
		
	return true;
}


	
