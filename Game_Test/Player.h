#pragma once
#include "GameObject.h"
#include "BlastCannon.h"
#include "GrappleGun.h"
#define PLAYER_SPRITE "assets/player/player_spritesheet.png"


class Player : public GameObject
{
private:
	static Player* instance;
	float speed;
	bool isSwitched;

	Player();
	~Player();

public:
	BlastCannon* blastCannon;
	GrappleGun* grappleGun;
	GameObject* currentWeapon;
	static Player* getInstance();
	void Initialize(LPDIRECT3DDEVICE9 device);
	//void Begin();
	void Update();
	//void SetTransform();
	void Draw();
	void ReleaseInstance();
	float getBlastOffAngle();
	void switchWeapon();
};

