#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "resource.h"
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720



class GameWindows
{
private:
	//	Window handle
	static GameWindows* instance;

	HWND g_hWnd;
	HINSTANCE hInstance;
	//	Window's structure
	WNDCLASS wndClass;
	bool isFullscreen;
	GameWindows();
	~GameWindows();
public:
	int r;
	int g;
	int b;
	static GameWindows* getInstance();
	void createWindow();
	void release();
	bool gameLoop();
	HWND getHWND();
	void setIsFullscreen(bool isFullScreen);
	bool getIsFullscreen();


};