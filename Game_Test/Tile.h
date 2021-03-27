#pragma once
#include "GameObject.h"
#define BRICK "assets/brick.png"
#define WINDOW "assets/window.png"
#define LAVA "assets/water.png"
#define GRASS "assets/grass.png"
#define TRAP "assets/spikes.png"

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
	//void setPosition(float x, float y, float z);
	void Render();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Grass :public GameObject
{
private:

public:
	Grass(float x, float y, float z);
	~Grass();
	//void setPosition(float x, float y, float z);
	void Render();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Door :public GameObject
{
private:

public:
	Door(float x, float y, float z);
	~Door();
	//void setPosition(float x, float y, float z);
	void Render();
	void Initialize(LPDIRECT3DDEVICE9 device);
};

class Trap :public GameObject
{
private:

public:
	Trap(float x, float y, float z);
	~Trap();
	//void setPosition(float x, float y, float z);
	void Render();
	void Initialize(LPDIRECT3DDEVICE9 device);
};