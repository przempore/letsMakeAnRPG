#include "StdAfx.h"
#include "Main.h"


CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	CameraX = 0;
	CameraY = 0;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	ForestArea = new CEnvironment(ScreenWidth,ScreenHeight, &CameraX, &CameraY, csdl_setup);


	MouseX = 0;
	MouseY = 0;

	bob = new MainCharacter(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, ForestArea);
}


CMain::~CMain(void)
{
	delete csdl_setup;

	delete bob;
}


void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX,&MouseY);
		ForestArea->DrawBack();

		bob->Draw();
		bob->Update();
		ForestArea->Update();

		ForestArea->DrawFront();
		csdl_setup->End();
	}
}