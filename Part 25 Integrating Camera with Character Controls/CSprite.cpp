// Let's Make An RPG - Part 25 - Sprite.cpp  www.youtube.com/youkondziu

#include "StdAfx.h"
#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY)
{
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer,FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image,NULL,NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;

	X_pos = x;
	Y_pos = y;

	Orgin_X = 0;
	Orgin_Y = 0;

	CurrentFrame = 0;
	Amount_Frame_X = 0;
	Amount_Frame_X = 0;
}

void CSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;
}

void CSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (animationDelay+Speed < SDL_GetTicks())
	{

		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		crop.x = CurrentFrame * (img_width/Amount_Frame_X);
		crop.y = Row * (img_height/Amount_Frame_Y);
		crop.w = img_width/Amount_Frame_X;
		crop.h = img_height/Amount_Frame_Y;

		animationDelay = SDL_GetTicks();
	}
}

CSprite::~CSprite(void)
{
	SDL_DestroyTexture(image);
}

void CSprite::DrawSteady()
{
	SDL_RenderCopy(renderer,image, &crop, &rect);
}

void CSprite::Draw()
{
	SDL_Rect Position;
	Position.x = rect.x + *CameraX;
	Position.y = rect.y + *CameraY;
	Position.w = rect.w;
	Position.h = rect.h;

	SDL_RenderCopy(renderer,image, &crop, &Position);


}

void CSprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - Orgin_X);
}

void CSprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - Orgin_Y);
}

void CSprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - Orgin_X);
	rect.y = int(Y_pos - Orgin_Y);
}

float CSprite::GetX()
{
	return X_pos;
}

float CSprite::GetY()
{
	return Y_pos;
}

void CSprite::SetOrgin(float X, float Y)
{
	Orgin_X = X;
	Orgin_Y = Y;

	SetPosition(GetX(), GetY());

}

void CSprite::SetWidth(int W)
{
	rect.w = W;
}

void CSprite::SetHeight(int H)
{
	rect.h = H;
}

int CSprite::GetWidth()
{
	return rect.w;
}

int CSprite::GetHeight()
{
	return rect.h;
}