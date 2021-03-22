#pragma once
#include "GameObject.h"
#include "DXLine.h"
#include "GameInput.h"
#define GRAPPLE_GUN "assets/player/grappling_hook_sprite.png"

class GrappleGun : public GameObject
{
private:
	DXLine* laserLine;

public:
	GrappleGun();
	~GrappleGun();

	void rotateGunBasedMouse();
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void Draw();
};

