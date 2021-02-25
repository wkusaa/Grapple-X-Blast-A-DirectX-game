#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#define MOSTIMA "mostima.png"
#define EXUSIAI "exusiai.png"


//	use int main if you want to have a console to print out message 
int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWindows* gWin = gWin->getInstance();
	GameGraphics* gGraphics = gGraphics->getInstance();
	GameInput* gInput = gInput->getInstance();
	gWin->createWindow();
	gGraphics->createDevice();
	gInput->createInput();


	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite = NULL;

	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(gGraphics->d3dDevice, &sprite);
	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(gGraphics->d3dDevice, MOSTIMA, &texture);


	//	Specify the "	" rectangle. // takes top left and bottom right
	RECT spriteRect;
	spriteRect.left = 189;
	spriteRect.top = 196;
	spriteRect.right = 310;
	spriteRect.bottom = 320;
	float pos = 512;
	D3DXVECTOR3 playerPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 playerPos2 = D3DXVECTOR3(1280, 0, 0);

	//HRESULT result;
	while (gWin->gameLoop())//it just works
	{

		gInput->update();
		//std::cout << gInput->mousePosition.x << "-" << gInput->mousePosition.x << std::endl;

		if (gInput->MouseButtonClick(0))
		{
			std::cout << "MouseClick" << std::endl;
		}

		gGraphics->clear();
		gGraphics->beginScene();


		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(texture, &spriteRect, NULL, D3DXVec3Add(&playerPos,&playerPos,&D3DXVECTOR3(0.5,0.5,0)), D3DCOLOR_XRGB(255, 255, 255));
		sprite->End();

		gGraphics->endScene();
		gGraphics->present();
	}

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	gInput->release();
	gGraphics->release();
	gWin->clearWindow();

	delete gInput;
	delete gGraphics;
	delete gWin;

	return 0;
}