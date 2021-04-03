#pragma once
#include <Windows.h>
#include "GameState.h"
#include "Player.h"
#include "PlayerController.h"
#include "GameStateManager.h"
#include "DXLine.h"
#include <iostream>
#include <vector>
#include "Tile.h"
#include "CollisionManager.h"
#include "GrapplingPoint.h"
#include "Key.h"
#include "Ammo.h"
#define BACKGROUND "assets/bg.png"

class TestLevel99 :public GameState
{
private:
	PlayerController* playerCon;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;
	std::vector<GrapplingPoint*> grapplePointArray;
	std::vector<Brick*> brickObject;
	std::vector<Grass*> grassObject;
	std::vector<Lava*> lavaObject;
	std::vector<Trap*> trapObject;
	std::vector<Ammo*> ammoObject;
	std::vector<Key*> keyObject;
	Door* doorObject;
	KeyUI* keyUI;
	CollisionManager* collision;
	bool isMoving;
	
public:
	TestLevel99();
	~TestLevel99();
	
	D3DXVECTOR3 gravity = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	D3DXVECTOR3 direction = D3DXVECTOR3(4.0f, -2.0f, 0.0f);

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	void buildLevel();
};
