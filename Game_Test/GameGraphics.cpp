#include "GameGraphics.h"

GameGraphics* GameGraphics::instance = 0;

GameGraphics::GameGraphics()
{
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dPP, sizeof(d3dPP));
}

GameGraphics::~GameGraphics()
{
	std::cout << "GameGraphics destroyed" << std::endl;
}

GameGraphics* GameGraphics::getInstance()
{
	if (!instance)
	{
		instance = new GameGraphics;
	}

	return instance;
}

//IDirect3DDevice9* GameDirectObject::getDevice()
//{
//	return d3dDevice;
//}

void GameGraphics::createDevice()
{
	GameWindows* gWin = gWin->getInstance();
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 1280;
	d3dPP.BackBufferHeight = 720;
	d3dPP.hDeviceWindow = gWin->getHWND();
	direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWin->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
}

void GameGraphics::clear()
{
	GameWindows* gWin = gWin->getInstance();
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(gWin->r, gWin->g, gWin->b), 1.0f, 0);
}

void GameGraphics::beginScene()
{
	d3dDevice->BeginScene();
}

void GameGraphics::endScene()
{
	d3dDevice->EndScene();
}

void GameGraphics::present()
{
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void GameGraphics::release()
{
	d3dDevice->Release();
	d3dDevice = NULL;

	delete instance;
	instance = 0;
}


