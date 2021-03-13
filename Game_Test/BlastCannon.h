#pragma once
#include "GameObject.h"
#include "GameInput.h"
#define BLAST_CANNON "assets/player/blast_cannon_sprite.png"

class BlastCannon : public GameObject
{
private:


public:
	BlastCannon();
	~BlastCannon();
	void rotateGunBasedMouse();
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void Draw();
	void Begin();
};
