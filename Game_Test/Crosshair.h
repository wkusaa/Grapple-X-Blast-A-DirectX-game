#pragma once
#include "GameObject.h"
#include "GameInput.h"
#define CROSSHAIR "assets/crosshair.png"

class Crosshair : public GameObject
{
private:

public:
	Crosshair();
	~Crosshair();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

