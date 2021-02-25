#include "GameWindows.h"

GameWindows* GameWindows::instance = 0;

GameWindows* GameWindows::getInstance()
{
	if (!instance)
	{
		instance = new GameWindows;
	}

	return instance;
}

GameWindows::GameWindows()
{
	this->r = 0;
	this->g = 128;
	this->b = 128;
	this->isFullscreen = false;
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
	this->wndClass = { 0 };
}


//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	GameWindows* gWin = gWin->getInstance();

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//std::cout << wParam << std::endl;
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			break;
		}
		else if (wParam == 70)
		{

			if (!gWin->getIsFullscreen())
			{
				gWin->setIsFullscreen(true);
			}
			else if (gWin->getIsFullscreen())
			{
				gWin->setIsFullscreen(false);
			}
		}



		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWindows::createWindow()
{
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACKONWHITE);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(BLAZE_CURSOR));
	//wndClass.hCursor = LoadCursorFromFile(AOT);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(GAME_ICON));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, 1298, 767, g_hWnd, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//	ShowCursor(false);

}



void GameWindows::clearWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool GameWindows::gameLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
		{

		}

		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);

	}

	/*
		Write your code here...
	*/


	return msg.message != WM_QUIT;
}

HWND GameWindows::getHWND()
{
	return this->g_hWnd;
}


void GameWindows::setIsFullscreen(bool con)
{
	isFullscreen = con;
}

bool GameWindows::getIsFullscreen()
{
	return this->isFullscreen;
}