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
	

	gravity = D3DXVECTOR3(0.0f, 0.02f, 0.0f);

	player->currentWeapon = player->blastCannon;
	player->currentWeapon->setPosition(player->position);
	isSwitched = true;

	angleDegree = 90;

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

void PlayerController::Update(std::vector<GrapplingPoint*> grapplePointArray)
{
	if (player->velocity.y > 0 && aState != Hook)
	{
		aState = FreeFall;
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
	action();
	animationController();


	if (aState == Idle || aState == FreeFall || aState == BlastOff || aState == Release || aState==Hook)
	{
		float magnitude = 10.0f;
		player->velocity = player->direction * magnitude;
		player->direction += gravity;
		player->velocity += gravity;
		player->position += player->velocity;

		if(aState == Hook)
		{
			onHook = grapplePointArray[1]; // set the currently hooked point
		}
	}
	else if (aState == Swinging)
	{
		//onHook = grapplePointArray[1]; // set the currently hooked point
		//D3DXVECTOR3 normalize;
		//D3DXVECTOR3 direction = onHook->position - player->position;
		//D3DXVec3Normalize(&normalize, &direction);
		//float angle = asin(normalize.x);

		float distanceFromPoint = 200.0f;
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
			angleDegree += 1;
		}
		else
		{
			angleDegree -= 1;
		}

		float angle = D3DXToRadian(angleDegree);
		float offsetX = (sin(angle)) * distanceFromPoint;
		float offsetY = (-cos(angle)) * distanceFromPoint;

		D3DXVECTOR3 prevPosition = player->position;
		D3DXVECTOR3 currentPosition = D3DXVECTOR3(grapplePointArray[1]->getPosition().x + offsetX, grapplePointArray[1]->getPosition().y + offsetY, 1.0f);
		D3DXVECTOR3 difPosition = currentPosition - prevPosition;


		player->setPosition(currentPosition);
		player->velocity *= 0;
		player->direction = D3DXVECTOR3(difPosition.x / 5, difPosition.y / 5, 0.0f);
	}

	player->Update();
	explosion->setPosition(player->blastCannon->position);
	explosion->Update();
	tempAState = aState; // don't ask me how
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
			aState = BlastOff;
			blastOff();
		}
		else if (weaponState == grappleGun)
		{
			switch (aState)
			{
			case FreeFall:
				aState = Hook;
				break;
			case Hook:
				aState = Swinging;
				break;
			case Swinging:
				aState = Release;
				break;
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
	std::cout << explosion->getCurrentFrame() << std::endl;
	explosion->setCurrentFrame(0);//reset
	explosion->setAnimationRow(0);

	std::cout << explosion->getCurrentFrame() << std::endl;
}

void PlayerController::hook()
{

}

void PlayerController::swing()
{

}

void PlayerController::releaseSwing()
{

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
		else if (weaponState == grappleGun && aState == Release)
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
