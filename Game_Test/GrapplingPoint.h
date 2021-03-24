#pragma once
#include "GameObject.h"
#define GRAPPLING_POINT "assets/platform/grappling_point.png"

class GrapplingPoint : public GameObject
{
private:

public:
	GrapplingPoint();
	GrapplingPoint(D3DXVECTOR3 position);
	~GrapplingPoint();

	void Initialize(LPDIRECT3DDEVICE9 device);
};

