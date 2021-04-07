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
	
	gravity = D3DXVECTOR3(0.0f, 0.10f, 0.0f);

	player->currentWeapon = player->blastCannon;
	player->currentWeapon->setPosition(player->position);
	isSwitched = true;
	isHooked = false;

	angleDegree = 90;
	magnitude = 5;
	hookLength = 200.0f;
	swingLength = 150.0f;

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
	
	blastOffSound = new GameSound(0, "assets/sound/sfx/explosion_27.wav", false);
	hookSound = new GameSound(0, "assets/sound/sfx/grappling_sfx.wav", false);
	swingSound = new GameSound(0, "assets/sound/sfx/jump_04.wav", false);
	releaseHookSound = new GameSound(0, "assets/sound/sfx/jump_11.wav", false);
	cannon_load = new GameSound(0, "assets/sound/sfx/cannon_switch.wav", false);
	grappling_load = new GameSound(0, "assets/sound/sfx/hook_switch.wav", false);
	deathSound = new GameSound(0, "assets/sound/sfx/snek_death.mp3", false);
}

PlayerController::~PlayerController()
{
	std::cout << "PlayerController destroyed" << std::endl;
	player->ReleaseInstance();

	delete line;
	delete explosion;

	delete blastOffSound;
	delete hookSound;
	delete swingSound;
	delete releaseHookSound;
	delete cannon_load;
	delete grappling_load;
	delete deathSound;
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


void PlayerController::Update(std::vector<GrapplingPoint*> grapplePointArray)
{
	if (player->velocity.y > 0 && aState != Hook && aState != Swinging && aState != Release && aState != Death)
	{
		aState = FreeFall;
	}
	else if (player->velocity.x == 0 && player->velocity.y == 0 && aState != Hook && aState != Swinging && aState != Release && aState != Death)
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

	if (aState != Death)
	{
		switchWeapon();

		if (weaponState == grappleGun)
		{
			if (aState != Swinging && aState != Release)
			{
				hook(grapplePointArray);
			}
		}

		action();
	}

	animationController();


	if (aState == Idle || aState == FreeFall || aState == BlastOff || aState == Release || aState == Hook)
	{
		player->velocity += gravity;
	}
	else if (aState == Swinging)
	{
		swing();
	}



	//std::cout << player->direction.x << "|" << player->direction.y << std::endl;
	if (player->isMoving == true && aState != Death)
	{
		//player->velocity = player->direction*magnitude;
		if (player->velocity.y > 5) player->velocity.y = 5;
		if (player->velocity.x > 5) player->velocity.x = 5;
		if (player->velocity.x < -5) player->velocity.x = -5;
		
		player->position += player->velocity;
		
	}
	else
	{
		//gravity = D3DXVECTOR3(0, 0, 0);
		player->velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
			blastOffSound->play();
			player->updateAmmoAmount(-1);
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
					hookSound->play();
				}
				else
				{
					aState = FreeFall;
				}
				//break;
			case Hook:
				if (onHook != NULL)
				{
					aState = Swinging;
					player->isMoving = true;
					player->position.y -= 30;
					player->updateAmmoAmount(-1);
				}
				else
				{
					aState = Idle;
				}
				break;
			case Swinging:
				aState = Release;
				releaseSwing();
				releaseHookSound->play();
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
	player->velocity = player->direction* 300/60;
	explosion->setCurrentFrame(0);//reset
	explosion->setAnimationRow(0);
}

void PlayerController::hook(std::vector<GrapplingPoint*> grapplePointArray)
{
	
	int tempNum = -1;

	for (int i = 0; i < grapplePointArray.size(); i++)
	{
		RECT relative = collision.relativeRect(grapplePointArray[i]->position, grapplePointArray[i]->getBounding_Box(), grapplePointArray[i]->getSpriteCentre());
		if (collision.checkMousePointCollision(relative) && checkHookLength(grapplePointArray[i]->position))
		{
			tempNum = i;
			break;
		}
	}

	if (tempNum < 0)
	{
		onHook = NULL;
		
	}
	else
	{
		onHook = grapplePointArray[tempNum];
	}

	
}

void PlayerController::swing()
{
	if (angleDegree > 270)
	{
		swingOppositeDirection = false;
		swingSound->play();
	}
	else if (angleDegree < 90)
	{
		swingOppositeDirection = true;
		swingSound->play();
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
	float offsetX = (sin(angle)) * swingLength;
	float offsetY = (-cos(angle)) * swingLength;

	D3DXVECTOR3 prevPosition = player->position;
	D3DXVECTOR3 currentPosition = D3DXVECTOR3(onHook->position.x + offsetX, onHook->position.y + offsetY, 1.0f);
	D3DXVECTOR3 difPosition = currentPosition - prevPosition;

	player->direction = D3DXVECTOR3(difPosition.x / 100, difPosition.y / 100, 0.0f);
	player->direction *= 300 / 60;//tweaks

	player->velocity = player->direction;
}

void PlayerController::releaseSwing()
{
	onHook = NULL;
}

bool PlayerController::checkHookLength(D3DXVECTOR3 pointPosition)
{
	float length = D3DXVec3Length(&(player->position - pointPosition));

	if (hookLength >= length)
	{
		return true;
	}

	return false;
}

void PlayerController::switchWeapon()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_H))
	{
		if (weaponState == blastCannon)
		{
			player->currentWeapon = player->grappleGun;
			weaponState = grappleGun;
			grappling_load->play();
		}
		else if (weaponState == grappleGun && (aState == FreeFall || aState == Idle))
		{
			player->currentWeapon = player->blastCannon;
			weaponState = blastCannon;
			cannon_load->play();
			cannon_load->setVolume(0.3f);
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
		line->draw(lineVertices, 2, D3DCOLOR_XRGB(0, 0, 0)); //bright blue
	}
	else
	{
		int lineScaling = 10;
		float scalarX = grappleGunPos.x + (mouseX - grappleGunPos.x) * lineScaling;
		float scalarY = grappleGunPos.y + (mouseY - grappleGunPos.y) * lineScaling;
		D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(grappleGunPos.x, grappleGunPos.y), D3DXVECTOR2(scalarX, scalarY) };

		if (onHook == NULL)
		{
			line->draw(lineVertices, 2, D3DCOLOR_XRGB(0, 255, 255)); //bright blue
		}
		else
		{
			line->draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 0)); //yellow
		}
		
	}
}

void PlayerController::TriggerDeath()
{
	//if (GameInput::getInstance()->KeyboardKeyPressed(DIK_D))
	{
		aState = Death;
		deathSound->play();
		player->velocity *= 0;
	}
}

void PlayerController::SetPlayerIdle()
{
	aState = Idle;
}