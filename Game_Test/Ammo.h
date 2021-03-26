#pragma once
#include "GameObject.h"
#define AMMO "assets/collectibles/ammo_spritesheet.png"

class Ammo : public GameObject
{
private:

public:
	Ammo();
	Ammo(D3DXVECTOR3 position);
	~Ammo();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

