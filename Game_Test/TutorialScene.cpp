#include "TutorialScene.h"


TutorialScene::TutorialScene()
{
	sprite = NULL;
	texture = NULL;

	device = GameGraphics::getInstance()->d3dDevice;

	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFileEx(device, TUTORIAL, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	rect_bg.left = 0;
	rect_bg.top = 0;
	rect_bg.right = 1280;
	rect_bg.bottom = 720;
}

TutorialScene::~TutorialScene()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void TutorialScene::init()
{
}

void TutorialScene::update()
{
}

void TutorialScene::fixedUpdate()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		GameStateManager::getInstance()->changeGameState(5);
	}
}

void TutorialScene::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &rect_bg, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void TutorialScene::release()
{

}
