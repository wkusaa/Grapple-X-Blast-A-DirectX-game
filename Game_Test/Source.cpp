#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameStateManager.h"
#include "GameSound.h"

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//check memory leaks
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();


	GameWindows* gWin = gWin->getInstance();
	gWin->createWindow();
	GameGraphics* gGraphics = gGraphics->getInstance();
	gGraphics->createDevice();
	GameInput* gInput = GameInput::getInstance();
	gInput->createInput();

	GameSound::Initialize();

	GameStateManager* gManager = gManager->getInstance();


	while (gWin->gameLoop())//it just works
	{
		gInput->update();

		gManager->update();
		gManager->fixedUpdate();

		GameSound::Update();

		gGraphics->beginScene();

		gManager->draw();
		gGraphics->endScene();
	}

	gInput->release();
	gGraphics->release();
	gWin->release();
	gManager->release();

	GameSound::Release();


	return 0;
}