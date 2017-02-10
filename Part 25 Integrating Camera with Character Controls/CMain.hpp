// Let's Make An RPG - Part 25 - Main.h  www.youtube.com/youkondziu

#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include <math.h> 

class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHeight);
	~CMain(void);
	void GameLoop();

private:

	MainCharacter *bob;

	int ScreenWidth;
	int ScreenHeight;

	bool quit;
	
	CSprite* grass;
	
	CSDL_Setup* csdl_setup;
	
	int MouseX;
	int MouseY;

	float CameraX;
	float CameraY;
};