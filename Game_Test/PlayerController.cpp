#include "PlayerController.h"


PlayerController* PlayerController::instance = 0;

PlayerController::PlayerController()
{
	std::cout << "PlayerController created" << std::endl;
	player = Player::getInstance();

	gravity = D3DXVECTOR3(0.0f, 0.05f, 0.0f);

	player->currentWeapon = player->blastCannon;
	player->currentWeapon->setPosition(player->position);
	isSwitched = true;
	weaponState = blastCannon;
}

PlayerController::~PlayerController()
{
	std::cout << "PlayerController destroyed" << std::endl;
	player->ReleaseInstance();
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

void PlayerController::Update()
{
	player->Update();
	
	switchWeapon();
	action();

	float magnitude = 20.0f;
	player->velocity = player->direction * magnitude;
	player->direction += gravity;
	player->velocity += gravity;
	player->position += player->velocity;
}


void PlayerController::Draw()
{
	player->Draw();
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
		else if (weaponState == grappleGun)
		{
			player->currentWeapon = player->blastCannon;
			weaponState = blastCannon;
		}
	}

}
