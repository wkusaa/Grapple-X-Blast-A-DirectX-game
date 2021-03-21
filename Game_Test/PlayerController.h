#pragma once
#include "Player.h"
class PlayerController
{
private:
	static PlayerController* instance;
	D3DXVECTOR3 gravity;

public:
	enum ActionState
	{
		BlastOff,
		Swinging
	}aState;

	enum WeaponState
	{
		blastCannon,
		grappleGun
	}weaponState;

	PlayerController();
	~PlayerController();
	Player* player;
	bool isSwitched;

	static PlayerController* getInstance();

	void Initialize();
	void Update();
	void Draw();
	void ReleaseInstance();

	void action();
	void blastOff();
	void hook();
	void swing();
	void releaseSwing();
	void switchWeapon();

};

