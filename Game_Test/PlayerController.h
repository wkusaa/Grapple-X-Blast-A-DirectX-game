#pragma once
#include "Player.h"
#include "GrapplingPoint.h"
#include "DXLine.h"
#include <vector>
class PlayerController
{
private:
	static PlayerController* instance;
	D3DXVECTOR3 gravity;
	DXLine* line;
	GrapplingPoint* onHook;

	float angleDegree;
	bool isSwitched;
	bool swingOppositeDirection;

public:
	enum ActionState
	{
		BlastOff,
		Hook,
		Swinging,
		Release,
		Idle

	}aState;

	enum WeaponState
	{
		blastCannon,
		grappleGun

	}weaponState;

	PlayerController();
	~PlayerController();

	Player* player;
	static PlayerController* getInstance();

	void Initialize();
	void Update(std::vector<GrapplingPoint*> grapplePointArray);
	void Draw();
	void ReleaseInstance();

	void action();
	void blastOff();
	void hook();
	void swing();
	void releaseSwing();
	void switchWeapon();
	void grappleDrawLaserLine();

};

