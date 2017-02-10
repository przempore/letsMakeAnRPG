#pragma once
#include "stdafx.h"
#include <vector>
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Tree.h"
#include <fstream>
#include <string>
#include <sstream>

class CEnvironment
{
public:
	CEnvironment(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~CEnvironment(void);


	void DrawBack();
	void DrawFront();

	void Update();

	void SaveToFile();
	void LoadFromFile();

	enum ModeType 
	{
		GamePlay,
		LevelCreation
	};

	std::vector<Tree*> GetTrees() { return trees; }

private:
	int Mode;
	CSDL_Setup* csdl_setup;
	float* CameraX;
	float* CameraY;

	bool OnePressed;
	CSprite* grass[4][7];

	std::vector<Tree*> trees;
};

