#include "DXLine.h"

DXLine::DXLine()
{
	std::cout << "Line created" << std::endl;
	line = NULL;
}

DXLine::~DXLine()
{
	std::cout << "Line destroyed" << std::endl;
	line->Release();
	line = NULL;
}

void DXLine::createLine(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateLine(device, &line);
}

void DXLine::draw(D3DXVECTOR2 lineVertices[], int verticeSize, D3DCOLOR color)
{

	//int verticeSize = sizeof(lineVertices);
	//std::cout << verticeSize << std::endl;
	line->Begin();
	line->Draw(lineVertices, 2, color);
	line->End();
}
