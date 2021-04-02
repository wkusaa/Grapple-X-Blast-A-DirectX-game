#pragma once
#include "GameObject.h"
#define KEYS "assets/collectibles/keys_spritesheet.png"
#define KEYUI "assets/keyUI.png"

class Key : public GameObject
{
private:

public:
	Key();
	~Key();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

class KeyUI : public GameObject
{
private:
	
public:
	KeyUI(D3DXVECTOR3 position);
	~KeyUI();
	int keyAmount;
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void render();
};
