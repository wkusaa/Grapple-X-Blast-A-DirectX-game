#include "GameGraphics.h"

GameGraphics* GameGraphics::instance = 0;

GameGraphics::GameGraphics()
{
	std::cout << "GameGraphics constructed" << std::endl;
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	r = 0;
	g = 0;
	b = 0;
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

void GameGraphics::createDevice()
{
	
	GameWindows* gWin = GameWindows::getInstance();
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;//windowed
	//d3dPP.BackBufferFormat = D3DFMT_X8B8G8R8;//fullscreen
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WIN_WIDTH;
	d3dPP.BackBufferHeight = WIN_HEIGHT;
	d3dPP.hDeviceWindow = gWin->getHWND();
	//d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWin->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
}

void GameGraphics::clear()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
}

void GameGraphics::beginScene()
{
	clear();
	d3dDevice->BeginScene();
}

void GameGraphics::endScene()
{
	d3dDevice->EndScene();
	present();
}

void GameGraphics::present()
{
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void GameGraphics::release()
{
	d3dDevice->Release();
	d3dDevice = NULL;

	direct3D9->Release();
	direct3D9 = NULL;

	delete instance;
	instance = NULL;
}

void GameGraphics::toggleFullscreen()
{

}