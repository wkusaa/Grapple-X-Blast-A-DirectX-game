#pragma once
#include "GameObject.h"
#include "DXLine.h"
#include "GameInput.h"
#define GRAPPLE_GUN "assets/player/grappling_hook_sprite.png"

class GrappleGun : public GameObject
{
private:
	//static BlastCannon* instance;
	DXLine* laserLine;

public:
	//BlastCannon* getInstance();
	GrappleGun();
	~GrappleGun();

	void rotateGunBasedMouse();
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void Draw();
	void drawLaserLine();
	void swingingFromGrapplePoint(D3DXVECTOR3 grapplePoint);
};

