#include "StartScene.h"

StartScene::StartScene()
{
	sprite = NULL;
	texture = NULL;

	device = GameGraphics::getInstance()->d3dDevice;

	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFileEx(device, STARTSCENE, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;

	mainMenuSound = new GameSound(1, "assets/sound/bgm/Jorge Hernandez - Chopsticks NO COPYRIGHT 8-bit Music.mp3", true);

	mainMenuSound->play();
	mainMenuSound->setVolume(0.3f);
}

StartScene::~StartScene()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	delete mainMenuSound;
}

void StartScene::init()
{
}

void StartScene::update()
{
}

void StartScene::fixedUpdate()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		mainMenuSound->stop();
		GameStateManager::getInstance()->changeGameState(1);
	}
}

void StartScene::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void StartScene::release()
{

}
