#pragma once
#include "GameObject.h"
#define GEMS "assets/collectibles/ruby_spritesheet.png"

class Gems : public GameObject
{
private:

public:
	Gems();
	Gems(D3DXVECTOR3 position);
	~Gems();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

