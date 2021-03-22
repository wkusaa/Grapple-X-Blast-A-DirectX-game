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

	weaponState = blastCannon;
	aState = BlastOff;
	angleDegree = 90;

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
	player->Update();

	switchWeapon();
	action();

	if (aState == BlastOff || aState == Release)
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
	std::cout << "Blast Off" << std::endl;
	float blastOffAngle = player->getBlastOffAngle();
	std::cout << blastOffAngle << std::endl;
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
