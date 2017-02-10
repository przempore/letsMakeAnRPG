#include "StdAfx.h"
#include "Tree.h"


Tree::Tree(int x_passed, int y_passed, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* csdl_setup)
{
	 CameraX = passed_CameraX;
	 CameraY = passed_CameraY;

	x = x_passed;
	y = y_passed;

	Trunk = new CSprite(csdl_setup->GetRenderer(),"data/environment/Trunk.png", x, y, 43, 145, CameraX, CameraY, CCollisionRectangle(0,110,43,36));
	Crown = new CSprite(csdl_setup->GetRenderer(),"data/environment/Crown.png", x-72, y-115, 183, 165, CameraX, CameraY, CCollisionRectangle());
}


Tree::~Tree(void)
{
	delete Crown;
	delete Trunk;
}

int Tree::GetX()
{
	return x;
}

int Tree::GetY()
{
	return y;
}

void Tree::DrawCrown()
{
		if ( 97 <= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();

	Crown->Draw();
}

void Tree::DrawTrunk()
{
	if ( 103 >= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();
}