// Let's Make An RPG - Part 25 - Sprite.h  www.youtube.com/youkondziu

#pragma once
class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY);
	
	~CSprite(void);

	void DrawSteady();
	void Draw();

	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);

	float GetX();
	float GetY();
	
	void SetWidth(int W);
	void SetHeight(int H);
	int GetWidth();
	int GetHeight();

	void SetOrgin(float X, float Y);
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);
private:
	float *CameraX;
	float *CameraY;

	float Orgin_X;
	float Orgin_Y;

	float X_pos;
	float Y_pos;

	SDL_Texture* image;
	SDL_Rect rect;

	SDL_Rect crop;

	int img_width;
	int img_height;
	int CurrentFrame;
	int animationDelay;

	int Amount_Frame_X;
	int Amount_Frame_Y;

	SDL_Renderer* renderer;
};