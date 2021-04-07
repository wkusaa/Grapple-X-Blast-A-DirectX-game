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
	std::cout << "GameWindows constructed" << std::endl;
	this->r = 163;
	this->g = 0;
	this->b = 0;
	this->isFullscreen = false;
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
	this->wndClass = { 0 };
}

GameWindows::~GameWindows()
{
	std::cout << "GameWindows destroyed" << std::endl;
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
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	RECT rect;
	ZeroMemory(&rect, sizeof(LPRECT));
	rect.top = 0;
	rect.left = 0;
	rect.bottom = WIN_HEIGHT;
	rect.right = WIN_WIDTH;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Grapple X Blast", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom, g_hWnd, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//ShowCursor(false);

}



void GameWindows::release()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);

	delete instance;
	instance = 0;
}

bool GameWindows::gameLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		////	Receive a quit message
		//if (msg.message == WM_QUIT)
		//{

		//}

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