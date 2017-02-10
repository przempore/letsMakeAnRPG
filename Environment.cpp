#include "Environment.h"


CEnvironment::CEnvironment(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup)
{
	csdl_setup = passed_csdl_setup;

	CameraX = passed_CameraX;
	CameraY  = passed_CameraY;

	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j] = new CSprite(csdl_setup->GetRenderer(),"data/environment/grass.bmp", ScreenWidth * i, ScreenHeight  * j, ScreenWidth, ScreenHeight, CameraX, CameraY, CCollisionRectangle());
		}
	}

	Mode = LevelCreation;
	LoadFromFile();

	OnePressed = false;
}


CEnvironment::~CEnvironment(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			delete grass[i][j];
		}

	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		delete (*i);
	}

	trees.clear();
}

void CEnvironment::DrawBack()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j]->Draw();
		}
	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		(*i)->DrawTrunk();
	}
}

void CEnvironment::DrawFront()
{
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		(*i)->DrawCrown();
	}
}

void CEnvironment::LoadFromFile()
{
	std::ifstream LoadedFile ("data/StageLayout.txt");

	std::string line;

	enum ObjectType{
		TypeNone,
		TypeTree
	};

	int CurrentType = TypeNone;

	if (LoadedFile.is_open())
	{
		while ( LoadedFile.good() )
		{
			std::getline(LoadedFile, line);
			if (line == "---====BEGIN_TREE====---")
			{
				CurrentType = TypeTree;
			}
			else if (line == "---====END_TREE====---")
			{
				CurrentType = TypeNone;
			}
			else
			{
				if (CurrentType == TypeTree)
				{

					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string PreviousWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;

						if (PreviousWord == "x:")
						{
							TempX = atoi( word.c_str() );
						}

						if (PreviousWord == "y:")
						{
							TempY = atoi( word.c_str() );

							trees.push_back(new Tree(TempX, TempY,CameraX, CameraY, csdl_setup));
						}

						PreviousWord = word;
					}


				}
			}
		}
	}
	else
	{
		std::cout << "File Could Not Be Open: StageLayout.txt" << std::endl;
	}
}

void CEnvironment::SaveToFile()
{
	std::ofstream LoadedFile;
	LoadedFile.open("data/StageLayout.txt");

	LoadedFile << "---====BEGIN_TREE====---" << std::endl;

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		LoadedFile << "x: " << (*i)->GetX() << "\ty: " << (*i)->GetY() << std::endl;

	}

	LoadedFile << "---====END_TREE====---" << std::endl;

	LoadedFile.close();

	std::cout << "Level Saved!" << std::endl;
}

void CEnvironment::Update()
{
	if (Mode == LevelCreation)
	{

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F11)
			{
				SaveToFile();
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F11)
			{
				OnePressed = false;
			}
		}



		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1)
			{
				trees.push_back(new Tree(-*CameraX+ 275,-*CameraY + 90,CameraX, CameraY, csdl_setup));
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1)
			{
				OnePressed = false;
			}
		}




		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F2)
			{
				if (trees.size() > 0)
				{

					delete trees[trees.size()-1];

					trees.pop_back();

				}
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F2)
			{
				OnePressed = false;
			}
		}
	}


	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{
		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
		{
			if (Mode == LevelCreation)
			{
				std::cout << "Level Creation: OFF" << std::endl;
				Mode = GamePlay;
			}
			else if (Mode == GamePlay)
			{
				std::cout << "Level Creation: ON" << std::endl;
				Mode = LevelCreation;
			}

			OnePressed = true;
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
	{
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F12)
		{
			OnePressed = false;
		}
	}

}
