#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameStateManager.h"
#include "GameSound.h"

//ken edited
//hello ken

//	use int main if you want to have a console to print out message 
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

	GameStateManager* gManager = gManager->getInstance();

	GameSound::Initialize();
	GameSound* myHero = new GameSound(1, "assets/sound/bgm/heroa.mp3", false);
	GameSound* bruh = new GameSound(0, "assets/sound/sfx/bruh.wav", true);

	myHero->play();
	bruh->play();

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

	delete bruh;
	delete myHero;
	GameSound::Release();


	return 0;
}