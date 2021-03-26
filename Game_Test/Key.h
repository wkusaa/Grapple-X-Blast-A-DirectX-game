#pragma once
#include "GameObject.h"
#define KEYS "assets/collectibles/keys_spritesheet.png"

class Key : public GameObject
{
private:

public:
	Key();
	~Key();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

