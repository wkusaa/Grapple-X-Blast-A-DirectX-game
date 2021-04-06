#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	sprite = NULL;
	texture = NULL;

	device = GameGraphics::getInstance()->d3dDevice;

	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFileEx(device, GAMEOVER, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;
}

GameOverScene::~GameOverScene()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void GameOverScene::init()
{
}

void GameOverScene::update()
{
}

void GameOverScene::fixedUpdate()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		GameStateManager* gManager = GameStateManager::getInstance();
		gManager->changeGameState(gManager->levelContinue);
	}
}

void GameOverScene::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void GameOverScene::release()
{
}
