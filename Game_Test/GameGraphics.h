#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GameWindows.h"
class GameGraphics
{
private:
	static GameGraphics* instance;
	GameGraphics();
	~GameGraphics();

public:
	int r;
	int g;
	int b;

	static GameGraphics* getInstance();
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3D9* direct3D9;
	IDirect3DDevice9* d3dDevice;//public pointer cuz getters and setters for this is cursed af
	void createDevice();
	void clear();
	void beginScene();
	void endScene();
	void present();
	void release();

	void toggleFullscreen();

};