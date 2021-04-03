#pragma once
#include "GameObject.h"
#define AMMO "assets/collectibles/ammo_spritesheet.png"
#define BULLETUI "assets/bulletUI.png"

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

class AmmoUI : public GameObject
{
private:
	static AmmoUI* instance;
public:
	AmmoUI();
	AmmoUI(D3DXVECTOR3 position);
	~AmmoUI();
	static AmmoUI* getInstance();
	int ammoAmount;
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void render();
};
