#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameStateManager.h"
#include <fmod.hpp>

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

	FMOD::System* system; //FMOD system object
	FMOD::Channel* bgChannel;
	FMOD::System_Create(&system); //Create FMOD system object
	system->init(100, FMOD_INIT_NORMAL, 0); //Initialize FMOD system

	FMOD::Sound* bgMusic;
	system->createStream("assets/sound/bgm/heroa.mp3", FMOD_DEFAULT, 0, &bgMusic);
	bgMusic->setMode(FMOD_LOOP_NORMAL);

	system->playSound(bgMusic, NULL, false, &bgChannel);




	while (gWin->gameLoop())//it just works
	{
		gInput->update();

		gManager->update();
		gManager->fixedUpdate();

		system->update();

		gGraphics->beginScene();

		gManager->draw();
		gGraphics->endScene();
	}

	gInput->release();
	gGraphics->release();
	gWin->release();
	gManager->release();

	bgMusic->release();
	system->release();

	return 0;
}