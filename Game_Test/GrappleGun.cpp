#include "GrappleGun.h"

GrappleGun::GrappleGun()
{
	std::cout << "GrappleGun created" << std::endl;
	texture = NULL;
	sprite = NULL;


	rotationCentre = D3DXVECTOR3(0, 0, 0);

	scaling = D3DXVECTOR3(0.5f, 0.5f, 1.0f);
	size = D3DXVECTOR3(128.0f, 64.0f, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0, 0, 0);
	mat = D3DMATRIX();

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	laserLine = new DXLine;
	laserLine->createLine(GameGraphics::getInstance()->d3dDevice);
}

GrappleGun::~GrappleGun()
{
	std::cout << "GrappleGun destroyed" << std::endl;
	delete laserLine;
}

void GrappleGun::rotateGunBasedMouse()
{
	GameInput* gInput = GameInput::getInstance();
	//float angle = atan2(position.y - gInput->mousePosition.y, position.x - gInput->mousePosition.x); // for gun facing left
	float angle = atan2(gInput->mousePosition.y - position.y, gInput->mousePosition.x - position.x); // for gun facing right
	setRotationAngle(angle);
}

void GrappleGun::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, GRAPPLE_GUN, &texture);
}

void GrappleGun::Update()
{
	rotateGunBasedMouse();
}

void GrappleGun::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	drawLaserLine();
}

void GrappleGun::drawLaserLine()
{
	D3DXVECTOR3 cannonPos = position;
	int lineScaling = 10;
	float mouseX = GameInput::getInstance()->mousePosition.x;
	float mouseY = GameInput::getInstance()->mousePosition.y;
	float scalarX = cannonPos.x + (mouseX - cannonPos.x) * lineScaling;
	float scalarY = cannonPos.y + (mouseY - cannonPos.y) * lineScaling;



	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(cannonPos.x, cannonPos.y), D3DXVECTOR2(scalarX, scalarY) };
	laserLine->draw(lineVertices, 2, D3DCOLOR_XRGB(0, 255, 255)); // bright red
}

void GrappleGun::swingingFromGrapplePoint(D3DXVECTOR3 grapplePoint)
{

}
