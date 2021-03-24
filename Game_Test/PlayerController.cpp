#include "PlayerController.h"


PlayerController* PlayerController::instance = 0;

PlayerController::PlayerController()
{
	std::cout << "PlayerController created" << std::endl;
	player = Player::getInstance();
	line = new DXLine;
	line->createLine(GameGraphics::getInstance()->d3dDevice);
	

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
	player->Initialize(GameGraphics::getInstance()->d3dDevice);
}

void PlayerController::Update(std::vector<GrapplingPoint*> grapplePointArray)
{


	switchWeapon();
	action();
	animationController();

	std::cout << player->velocity.x << "|" << player->velocity.y << std::endl;
	//std::cout << aState << std::endl;

	if (player->velocity.y > 0)
	{
		aState = FreeFall;
	}

	if (aState == Idle || aState == FreeFall || aState == BlastOff || aState == Release)
	{
		float magnitude = 10.0f;
		player->velocity = player->direction * magnitude;
		player->direction += gravity;
		player->velocity += gravity;
		player->position += player->velocity;
	}
	else if (aState == Swinging)
	{
		float distanceFromPoint = 400.0f;
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

		D3DXVECTOR3 currentPosition = D3DXVECTOR3(grapplePointArray[1]->getPosition().x + offsetX, grapplePointArray[1]->getPosition().y + offsetY, 1.0f);
		onHook = grapplePointArray[1]; // set the currently hooked point
		player->setPosition(currentPosition);
		player->velocity *= 0;
		player->direction = D3DXVECTOR3(sin(angleDegree), -cos(angleDegree), 0.0f);
	}
	player->Update();
	tempAState = aState; // don't ask me how
}


void PlayerController::Draw()
{
	player->Draw();

	if (weaponState == grappleGun)
	{
		grappleDrawLaserLine();
	}
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
			case BlastOff:
				aState = Swinging;
				break;
			case Swinging:
				aState = Release;
				break;
			case Release:
				aState = BlastOff;
				break;
			default:
				break;
			}
		}
	}
}

void PlayerController::blastOff()
{
	//std::cout << "Blast Off" << std::endl;
	float blastOffAngle = player->getBlastOffAngle();
	//std::cout << blastOffAngle << std::endl;
	player->direction = D3DXVECTOR3(sin(blastOffAngle), -cos(blastOffAngle), 0.0f);
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
