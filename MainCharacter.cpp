#include "MainCharacter.h"


MainCharacter::MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CEnvironment* passed_Environment)
{
	Environment = passed_Environment;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	csdl_setup = passed_SDL_Setup;
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;

	bob = new CSprite(csdl_setup->GetRenderer(),"data/tom.png", 300,250, 100,120, CameraX, CameraY,CCollisionRectangle(275, 220, 50, 30));
	bob->SetUpAnimation(4,4);
	bob->SetOrgin(bob->GetWidth()/2.0f, bob->GetHeight());

	timeCheck = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;
}


MainCharacter::~MainCharacter(void)
{
	delete bob;
}

void MainCharacter::Draw()
{
	bob->DrawSteady();
}

void MainCharacter::UpdateAnimation()
{
	float angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
	angle = (angle * (180/3.14)) + 180;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//down
			if (distance > 15)
				bob->PlayAnimation(0,3,0,200);
			else
				bob->PlayAnimation(1,1,0,200);

		}
		else if (angle > 135 && angle <= 225)
		{
			//left
			if (distance > 15)
				bob->PlayAnimation(0,3,1,200);
			else
				bob->PlayAnimation(1,1,1,200);
		}
		else if (angle > 225 && angle <= 315)
		{
			//up
			if (distance > 15)
				bob->PlayAnimation(0,3,3,200);
			else
				bob->PlayAnimation(1,1,3,200);

		}
		else if ((angle <= 360 && angle > 315) || (angle >=0 && angle <= 45))
		{
			//right
			if (distance > 15)
				bob->PlayAnimation(0,3,2,200);
			else
				bob->PlayAnimation(1,1,2,200);

		}
	}
}

void MainCharacter::UpdateControls()
{
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
	{
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			Follow_Point_X = *CameraX - *MouseX + 300;
			Follow_Point_Y = *CameraY - *MouseY + 250;
			Follow = true;
		}
	}

	if (timeCheck+10 < SDL_GetTicks() && Follow)
	{
		distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);

		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;

		if (distance > 15)
		{
			bool collding = false;

			for (int i = 0; i < Environment->GetTrees().size(); i++)
			{
				if (bob->isColliding(Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect()))
				{
					if (*CameraX > Follow_Point_X)
					{
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X)
					{
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y)
					{
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y)
					{
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;
					collding = true;
				}
			}

			if (!collding)
			{
				if (*CameraX != Follow_Point_X)
				{
					*CameraX = *CameraX -  (((*CameraX-Follow_Point_X)/distance) * 2.7f);
				}

			if (*CameraY != Follow_Point_Y)
				{
					*CameraY = *CameraY -  (((*CameraY-Follow_Point_Y)/distance) * 2.7f);
				}
			}
		}
		else
			Follow = false;

		timeCheck = SDL_GetTicks();
	}
}

void MainCharacter::Update()
{
	UpdateAnimation();
	UpdateControls();

}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}