#include "PlayerController.h"


PlayerController* PlayerController::instance = 0;

PlayerController::PlayerController()
{
	std::cout << "PlayerController created" << std::endl;
	player = Player::getInstance();
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	line = new DXLine;
	line->createLine(GameGraphics::getInstance()->d3dDevice);

	explosion = new Explosion;
	explosion->setPosition(player->blastCannon->position);
	

	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);

	player->currentWeapon = player->blastCannon;
	player->currentWeapon->setPosition(player->position);
	isSwitched = true;

	angleDegree = 90;
	magnitude = 5;

	onHook = NULL;

	animationCount[BlastOff] = 4;
	animationCount[Hook] = 4;
	animationCount[Swinging] = 2;
	animationCount[Release] = 2;
	animationCount[Idle] = 8;
	animationCount[FreeFall] = 8;
	animationCount[Death] = 7;
	animationCount[GetHit] = 4;

	weaponState = blastCannon;
	aState = Idle;
	tempAState = aState;
	
}

void PlayerController::animationController()
{
	
	switch (aState)
	{
	case PlayerController::BlastOff:
		player->setAnimationCount(animationCount[BlastOff]);
		player->setAnimationRow(BlastOff);
		player->setAnimationLoop(false);
		break;
	case PlayerController::Hook:
		player->setAnimationCount(animationCount[Hook]);
		player->setAnimationRow(Hook);
		player->setAnimationLoop(false);
		break;
	case PlayerController::Swinging:
		player->setAnimationCount(animationCount[Swinging]);
		player->setAnimationRow(Swinging);
		player->setAnimationLoop(false);
		break;
	case PlayerController::Release:
		player->setAnimationCount(animationCount[Release]);
		player->setAnimationRow(Release);
		player->setAnimationLoop(false);
		break;
	case PlayerController::Idle:
		player->setAnimationCount(animationCount[Idle]);
		player->setAnimationRow(Idle);
		player->setAnimationLoop(true);
		break;
	case PlayerController::FreeFall:
		player->setAnimationCount(animationCount[FreeFall]);
		player->setAnimationRow(FreeFall);
		player->setAnimationLoop(true);
		break;
	case PlayerController::Death:
		player->setAnimationCount(animationCount[Death]);
		player->setAnimationRow(Death);
		player->setAnimationLoop(false);
		break;
	case PlayerController::GetHit:
		player->setAnimationCount(animationCount[GetHit]);
		player->setAnimationRow(GetHit);
		player->setAnimationLoop(false);
		break;
	default:
		break;
	}

	if (tempAState != aState)
	{
		player->setCurrentFrame(0);
	}
}


PlayerController::~PlayerController()
{
	std::cout << "PlayerController destroyed" << std::endl;
	player->ReleaseInstance();
	delete line;
	delete explosion;
}

PlayerController* PlayerController::getInstance()
{
	if (!instance)
	{
		instance = new PlayerController;
	}

	return instance;
}

void PlayerController::Initialize()
{
	GameGraphics* gameGraphics = GameGraphics::getInstance();
	player->Initialize(gameGraphics->d3dDevice);
	explosion->Initialize(gameGraphics->d3dDevice);
}

//void PlayerController::Update(std::vector<GrapplingPoint*> grapplePointArray)
//{
//	if (player->velocity.y > 0 && aState != Hook && aState != Swinging)
//	{
//		aState = FreeFall;
//	}
//	if (player->velocity.x > 0)
//	{
//		player->scaling.x = abs(player->scaling.x);
//	}
//	else if (player->velocity.x < 0)
//	{
//		player->scaling.x = -abs(player->scaling.x);
//	}
//
//	switchWeapon();
//
//	if (weaponState == grappleGun && onHook == NULL)
//	{
//		hook(grapplePointArray);
//	}
//
//	action();
//	animationController();
//
//	//if (player->velocity.x == 0 && player->velocity.y == 0)
//	//{
//	//	aState = Idle;
//	//}
//
//
//	if (aState == Idle || aState == FreeFall || aState == BlastOff || aState == Release || aState == Hook)
//	{
//		float magnitude = 10.0f;
//		player->velocity = player->direction * magnitude;
//		player->direction += gravity;
//		player->velocity += gravity;
//		player->position += player->velocity;
//
//	}
//	else if (aState == Swinging)
//	{
//
//		float distanceFromPoint = 200.0f;
//		if (angleDegree > 270)
//		{
//			swingOppositeDirection = false;
//		}
//		else if (angleDegree < 90)
//		{
//			swingOppositeDirection = true;
//		}
//
//		if (swingOppositeDirection)
//		{
//			angleDegree += 1;
//		}
//		else
//		{
//			angleDegree -= 1;
//		}
//
//		float angle = D3DXToRadian(angleDegree);
//		float offsetX = (sin(angle)) * distanceFromPoint;
//		float offsetY = (-cos(angle)) * distanceFromPoint;
//
//		D3DXVECTOR3 prevPosition = player->position;
//		D3DXVECTOR3 currentPosition = D3DXVECTOR3(onHook->position.x + offsetX, onHook->position.y + offsetY, 1.0f);
//		D3DXVECTOR3 difPosition = currentPosition - prevPosition;
//
//
//		player->setPosition(currentPosition);
//		player->velocity *= 0;
//		player->direction = D3DXVECTOR3(difPosition.x / 5, difPosition.y / 5, 0.0f);
//	}
//
//	player->Update();
//
//	explosion->setPosition(player->blastCannon->position);
//	explosion->Update();
//
//
//	tempAState = aState; // it just works and i don't really understand myself
//}

void PlayerController::Update(std::vector<GrapplingPoint*> grapplePointArray)
{
	if (player->velocity.y > 0 && aState != Hook && aState != Swinging && aState != Release)
	{
		aState = FreeFall;
	}
	else if (player->velocity.x == 0 && player->velocity.y == 0 && aState != Hook && aState != Swinging && aState != Release)
	{
		aState = Idle;
	}

	if (player->velocity.x > 0)
	{
		player->scaling.x = abs(player->scaling.x);
	}
	else if (player->velocity.x < 0)
	{
		player->scaling.x = -abs(player->scaling.x);
	}

	switchWeapon();

	if (weaponState == grappleGun)
	{
		if (onHook == NULL)
		{
			hook(grapplePointArray);
		}

	}

	std::cout << aState << std::endl;


	action();
	animationController();


	if (aState == Idle || aState == FreeFall || aState == BlastOff || aState == Release || aState == Hook)
	{
		player->direction += gravity;
		player->velocity += gravity;
	}
	else if (aState == Swinging)
	{

		float distanceFromPoint = 150.0f;
		if (angleDegree > 270)
		{
			swingOppositeDirection = false;
		}
		else if (angleDegree < 90)
		{
			swingOppositeDirection = true;
		}

		if (swingOppositeDirection)
		{
			angleDegree += 2;
		}
		else
		{
			angleDegree -= 2;
		}

		float angle = D3DXToRadian(angleDegree);
		float offsetX = (sin(angle)) * distanceFromPoint;
		float offsetY = (-cos(angle)) * distanceFromPoint;

		D3DXVECTOR3 prevPosition = player->position;
		D3DXVECTOR3 currentPosition = D3DXVECTOR3(onHook->position.x + offsetX, onHook->position.y + offsetY, 1.0f);
		D3DXVECTOR3 difPosition = currentPosition - prevPosition;

		player->direction = D3DXVECTOR3(difPosition.x / 100, difPosition.y / 100, 0.0f);
		player->direction *= 0.45;
	}



	//std::cout << player->direction.x << "|" << player->direction.y << std::endl;
	if (player->isMoving == true)
	{
		player->velocity = player->direction * magnitude;
		if (player->velocity.y > 5) player->velocity.y = 5;
		if (player->velocity.x > 5) player->velocity.x = 5;
		if (player->velocity.x < -5) player->velocity.x = -5;
		
		player->position += player->velocity;
		
	}
	else
	{
		player->velocity = D3DXVECTOR3(0,0,0);
		player->position += player->velocity;
	}

	player->Update();


	explosion->setPosition(player->blastCannon->position);
	explosion->Update();


	tempAState = aState; // it just works and i don't really understand myself
}


void PlayerController::Draw()
{
	player->Draw();

	if (weaponState == grappleGun)
	{
		grappleDrawLaserLine();
	}

	explosion->Draw();
}

void PlayerController::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}

void PlayerController::action()
{
	if (GameInput::getInstance()->MouseButtonClick(0))
	{
		if (weaponState == blastCannon)
		{
			player->isMoving = true;
			aState = BlastOff;
			blastOff();
			AmmoUI::getInstance()->ammoAmount -= 1;
		}
		else if (weaponState == grappleGun)
		{
			switch (aState)
			{
			case Idle:
			case FreeFall:
				if (onHook != NULL)
				{
					aState = Hook;
					
				}
				else
				{
					aState = FreeFall;
				}
				break;
			case Hook:
				aState = Swinging;
				player->isMoving = true;
				player->position.y += 1;
				break;
			case Swinging:
				aState = Release;
				releaseSwing();
				player->direction *= 3.0;
			case Release:
				aState = FreeFall;
				break;
			default:
				break;
			}
		}
	}
}

void PlayerController::blastOff()
{
	float blastOffAngle = player->getBlastOffAngle();
	player->direction = D3DXVECTOR3(sin(blastOffAngle), -cos(blastOffAngle), 0.0f);
	explosion->setCurrentFrame(0);//reset
	explosion->setAnimationRow(0);
}

void PlayerController::hook(std::vector<GrapplingPoint*> grapplePointArray)
{
	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		RECT relative = collision.relativeRect(grapplePointArray[i]->position, grapplePointArray[i]->getBounding_Box(), grapplePointArray[i]->getSpriteCentre());
		if (collision.checkMousePointCollision(relative))
		{
			onHook = grapplePointArray[i];
			break;
		}
	}
}

void PlayerController::swing()
{

}

void PlayerController::releaseSwing()
{
	onHook = NULL;
}

void PlayerController::switchWeapon()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_H))
	{
		if (weaponState == blastCannon)
		{
			player->currentWeapon = player->grappleGun;
			weaponState = grappleGun;
		}
		else if (weaponState == grappleGun && (aState == FreeFall || aState == Idle))
		{
			player->currentWeapon = player->blastCannon;
			weaponState = blastCannon;
		}
	}

}

void PlayerController::grappleDrawLaserLine()
{
	D3DXVECTOR3 grappleGunPos = player->grappleGun->position;
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;

	//std::cout << mouseX << "|" << mouseY << std::endl;

	if (aState == Swinging)
	{
		D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(grappleGunPos.x, grappleGunPos.y), D3DXVECTOR2(onHook->position.x,onHook->position.y) };
		line->draw(lineVertices, 2, D3DCOLOR_XRGB(0, 255, 255)); //bright blue
	}
	else
	{
		int lineScaling = 10;
		float scalarX = grappleGunPos.x + (mouseX - grappleGunPos.x) * lineScaling;
		float scalarY = grappleGunPos.y + (mouseY - grappleGunPos.y) * lineScaling;
		D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(grappleGunPos.x, grappleGunPos.y), D3DXVECTOR2(scalarX, scalarY) };
		line->draw(lineVertices, 2, D3DCOLOR_XRGB(0, 255, 255)); //bright blue
	}
}