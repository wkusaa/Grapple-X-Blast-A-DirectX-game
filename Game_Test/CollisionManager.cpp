#include "CollisionManager.h"


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

bool CollisionManager::checkCollision(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbBox, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize, int tileType, int playerAction, D3DXVECTOR3& playerVel)
{
	if (collisionDetect(playerPos, playerBbBox, gameObjectPos, gameObjectBbSize))
	{
		printf("%f     %f     %f      %f\n", gameObjectBbSize.x, gameObjectBbSize.y, playerBbBox.x, playerBbBox.y);
		//calculate distance between center of bounding box and center of object 
		float w = 0.5 * (playerBbBox.x + gameObjectBbSize.x);
		float h = 0.5 * (playerBbBox.y + gameObjectBbSize.y);

		//calculate distance between position of player and object
		float dx = playerPos.x - gameObjectPos.x;
		float dy = playerPos.y - gameObjectPos.y;

		if (playerAction == 2) return false;//player dead

		if (abs(dx) <= w && abs(dy) <= h)
		{
			if (playerAction == 3) return true;//swinging action no collision
			if (tileType == 2) return true;//for collectible items

			float wy = w * dy;
			float hx = h * dx;

			//switch (tileType)
			//{
			//case 0:
			//	break;
			//case 1:
			//	break;
			//case 2:
			//	return true;//for collectible items
			//	break;
			//case 4://spike
			//	if (wy > hx)
			//	{
			//		if (wy > -hx)
			//		{
			//			playerVel.y = -playerVel.y*0.9;
			//			printf("bottom\n");
			//			/* collision at the bottom */
			//		}
			//	}
			//	else
			//	{
			//		if (wy < -hx)
			//			playerVel.y = -playerVel.y*0.9;
			//			printf("top\n");/* at the top */

			//			if (tileType == 1)//floor, so can stand on it
			//			{
			//				Player::getInstance()->isMoving = false;
			//			}
			//		}
			//	}
			//	
			//}
			//if (tileType == 2) return true;//for collectible items
			///* collision! */
			//

			if (wy > hx)
			{
				if (wy > -hx)
				{
					playerVel.y = -playerVel.y*0.9;
					printf("bottom\n");
					/* collision at the bottom */
				}
				else
				{
					playerVel.x = -playerVel.x*0.9;
					printf("left\n");
					/* on the left */
				}
			}
			else
			{
				if (wy > -hx)
				{
					playerVel.x = -playerVel.x*0.9;
					printf("right\n");/* on the right */
				}
				else
				{
					playerVel.y = -playerVel.y*0.9;
					printf("top\n");/* at the top */

					if (tileType == 1)//floor, so can stand on it
					{
						Player::getInstance()->isMoving = false;
					}

				}
			}
			return true;
		}
	}
	return false;
}

bool CollisionManager::collisionDetect(D3DXVECTOR3 playerPos, D3DXVECTOR3 playerBbSize, D3DXVECTOR3 gameObjectPos, D3DXVECTOR3 gameObjectBbSize)
{
	float characterCenterX = playerBbSize.x / 2;
	float characterCenterY = playerBbSize.y / 2;
	float playerRight = playerPos.x + characterCenterX;
	float playerLeft = playerPos.x - characterCenterX;
	float playerBottom = playerPos.y + characterCenterY;
	float playerTop = playerPos.y - characterCenterY;
	
	float objectCenterX = gameObjectBbSize.x / 2;
	float objectCenterY = gameObjectBbSize.y / 2;
	float objectRight = gameObjectPos.x + objectCenterX;
	float objectLeft = gameObjectPos.x - objectCenterX;
	float objectBottom = gameObjectPos.y + objectCenterY;
	float objectTop = gameObjectPos.y - objectCenterY;
	
	if (playerBottom > objectTop && playerTop < objectBottom && playerRight > objectLeft && playerLeft < objectRight) return true;
		
	return false;
}



	
