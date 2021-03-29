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
#define BACKGROUND "assets/bg.png"
#define GRASS "assets/grass.png"
#define BRICK "assets/brick.png"

class TestLevel99 :public GameState
{
private:
	//GameObject* player;
	D3DXVECTOR3 playerPos;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture_brick;
	LPDIRECT3DTEXTURE9 texture_player;
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	RECT rect_bg;
	RECT rect_brick;
	//D3DXVECTOR3 brick_pos[10];
	D3DXVECTOR3 characterCenter;
	std::vector<Brick*> brickObject;
	std::vector<Grass*> grassObject;
	std::vector<Lava*> lavaObject;
	std::vector<Trap*> trapObject;
	Door* doorObject;
	CollisionManager* collision;
	
	//std::vector<GAMEOBJECT> gameObjects;
	bool isMoving;
	
	//std::vector<GrapplingPoint*> grapplePointArray;

public:
	TestLevel99();
	~TestLevel99();

	float rotation = 0;
	D3DXVECTOR3 gravity = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	D3DXVECTOR3 direction = D3DXVECTOR3(4.0f, -2.0f, 0.0f);
	//DXLine* line;

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	
	bool checkCollision(D3DXVECTOR3 pos1,RECT rect1, D3DXVECTOR3 pos2, RECT rect2); 
	int checkSideCollide(D3DXVECTOR3 player, D3DXVECTOR3 object); //1 = right, 2 = top, 3= bottom, 4 = left
};
