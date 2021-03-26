#pragma once
#include "GameObject.h"
#define EXPLOSION "assets/effects/explosion_spritesheet.png"

class Explosion : public GameObject
{
private:

public:
	Explosion();
	Explosion(D3DXVECTOR3 position);
	~Explosion();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

