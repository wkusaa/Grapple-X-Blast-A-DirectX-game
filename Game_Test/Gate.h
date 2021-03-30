#pragma once
#include "GameObject.h"
#define GATE "assets/platform/door_spritesheet.png"

class Gate : public GameObject
{
private:

public:
	Gate();
	Gate(D3DXVECTOR3 position);
	~Gate();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();

};

