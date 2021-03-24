#pragma once
#include "Player.h"
#include "GrapplingPoint.h"
#include "DXLine.h"
#include <vector>
class PlayerController : public GameObject
{
private:
	static PlayerController* instance;
	D3DXVECTOR3 gravity;
	DXLine* line;
	GrapplingPoint* onHook;

	float angleDegree;
	bool isSwitched;
	bool swingOppositeDirection;
	int animationCount[8];
	int tempAState;

public:
	enum ActionState
	{
		BlastOff = 6,
		Hook = 7,
		Swinging = 3,
		Release = 4,
		Idle = 0,
		FreeFall = 1,
		Death = 2,
		GetHit = 5

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

	void animationController();

};

