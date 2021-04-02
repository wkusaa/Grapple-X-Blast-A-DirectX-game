#pragma once
#include "GameObject.h"
#define BRICK "assets/brick.png"
#define WINDOW "assets/window.png"
#define LAVA "assets/water.png"
#define GRASS "assets/grass.png"
#define TRAP "assets/spikes.png"
#define PLATFORM1 "assets/platform/Platform01.png"
#define PLATFORM2 "assets/platform/Platform02.png"
#define PLATFORM3 "assets/platform/Platform03.png"
#define PLATFORM4 "assets/platform/Platform04.png"
#define PLATFORM5 "assets/platform/Platform05.png"
#define SPIKE "assets/platform/spikes_spritesheet.png"
#define BRAZIER "assets/platform/brazier_spritesheet.png"

class Brick :public GameObject
{
private:
	
public:
	Brick(float x, float y, float z);
	~Brick();
	//void setPosition(float x, float y, float z);
	void Render();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Lava :public GameObject
{
private:

public:
	Lava(float x, float y, float z);
	~Lava();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Grass :public GameObject
{
private:

public:
	Grass(float x, float y, float z);
	~Grass();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Door :public GameObject
{
private:

public:
	Door(float x, float y, float z);
	~Door();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Trap :public GameObject
{
private:

public:
	Trap(float x, float y, float z);
	~Trap();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Platform : public GameObject
{
private:
	int platformType;
public:
	//BlastCannon* getInstance();
	Platform();
	Platform(int platformType);
	Platform(int platformType, float x, float y, float z);
	~Platform();

	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Spike : public GameObject
{
private:

public:
	Spike();
	Spike(D3DXVECTOR3 position);
	~Spike();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};

class Brazier : public GameObject
{
private:

public:
	Brazier();
	Brazier(D3DXVECTOR3 position);
	~Brazier();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
};
