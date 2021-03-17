#pragma once
#include <d3dx9.h>
#include "GameGraphics.h"
class DXLine
{
private:


public:
	DXLine();
	~DXLine();

	LPD3DXLINE line;

	void createLine(LPDIRECT3DDEVICE9 device);
	void draw(D3DXVECTOR2 lineVertices[], int verticeSize, D3DCOLOR color);
};