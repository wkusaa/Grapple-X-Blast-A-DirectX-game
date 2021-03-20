#include "PlayerController.h"

PlayerController::PlayerController()
{
	std::cout << "PlayerController created" << std::endl;
	player = Player::getInstance();
}

PlayerController::~PlayerController()
{
	std::cout << "PlayerController destroyed" << std::endl;
}

void PlayerController::Update()
{

}
