#pragma once
#include "Player.h"
#include "GrapplingPoint.h"
#include "DXLine.h"
#include "Explosion.h"
#include "CollisionManager.h"
#include "Ammo.h"
#include "GameSound.h"
#include <vector>
class PlayerController
{
private:
	static PlayerController* instance;
	D3DXVECTOR3 gravity;
	DXLine* line;
	GrapplingPoint* onHook;
	Explosion* explosion;
	CollisionManager collision;
	
	float angleDegree;
	bool isSwitched;
	bool isHooked;
	bool swingOppositeDirection;
	int animationCount[8];
	int tempAState;
	float magnitude;
	float hookLength;
	float swingLength;

	GameSound* blastOffSound;
	GameSound* hookSound;
	GameSound* swingSound;
	GameSound* releaseHookSound;
	GameSound* cannon_load;
	GameSound* grappling_load;
	GameSound* deathSound;

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
	void hook(std::vector<GrapplingPoint*> grapplePointArray);
	void swing();
	void releaseSwing();
	bool checkHookLength(D3DXVECTOR3 pointPosition);
	void switchWeapon();
	void grappleDrawLaserLine();
	void TriggerDeath();
	void SetPlayerIdle();
	void animationController();

};

