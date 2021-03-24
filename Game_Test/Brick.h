#pragma once
#include "GameObject.h"


class Brick :public GameObject
{
private:

public:
	Brick();
	~Brick();
	void Draw(float x, float y, float z);
	void Initialize(LPDIRECT3DDEVICE9 device);
};
