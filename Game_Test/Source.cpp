#include "GameWindows.h"
#include "GameGraphics.h"
#include "GameInput.h"
#include "GameStateManager.h"
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

	
	GameStateManager* gManager = gManager->getInstance();
	while (gWin->gameLoop())//it just works
	{

		
		gInput->update();

		if (gInput->MouseButtonClick(0))
		{
			std::cout << "MouseClick" << std::endl;
		}

		gGraphics->clear();
		gGraphics->beginScene();

		gManager->currentGameState->update();
		gManager->currentGameState->draw();


		gGraphics->endScene();
		gGraphics->present();
	}

	gInput->release();
	gGraphics->release();
	gWin->clearWindow();

	delete gInput;
	//delete gGraphics; //private destructor test
	delete gWin;


	gManager->releaseInstance();
	delete gManager;
	gManager = NULL;
	//destructor check

	return 0;
}