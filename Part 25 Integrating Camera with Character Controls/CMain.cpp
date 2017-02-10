// Let's Make An RPG - Part 25 - Main.cpp  www.youtube.com/youkondziu

#include "StdAfx.h"
#include "Main.h"


CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	CameraX = 300;
	CameraY = 250;

	grass = new CSprite(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight, &CameraX, &CameraY);
	MouseX = 0;
	MouseY = 0;

	bob = new MainCharacter(csdl_setup, &MouseX, &MouseY, &CameraX,&CameraY);
}


CMain::~CMain(void)
{
	delete csdl_setup;
	delete grass;
	delete bob;
}


void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX,&MouseY);

		grass->Draw();
		bob->Draw();

		bob->Update();

		csdl_setup->End();
	}
}