#pragma once
#include "GameObject.h"
#include "Player.h"
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
	
public:
	AmmoUI();
	AmmoUI(D3DXVECTOR3 position);
	~AmmoUI();
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void Draw();

};
