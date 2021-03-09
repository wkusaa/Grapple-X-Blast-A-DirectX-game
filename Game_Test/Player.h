#pragma once
#include "GameObject.h"
#define PLAYER_SPRITE "assets/player/player_spritesheet.png"


class Player : public GameObject
{
private:
	static Player* instance;
	float speed;
	Player();
	~Player();
public:
	static Player* getInstance();
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Begin();
	void Update();
	void SetTransform(D3DXMATRIX mat);
	void Draw();
	void ReleaseInstance();
};

