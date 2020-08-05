#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include "Animation.h"


class Bullet {
public:
	Bullet(int X, int Y, std::string fileName);
	Bullet(int X, int Y, std::string fileName, int rows, int columns);
	void setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame);
	void Draw(Graphics &gfx);
	void Accelerate(int direction, int speed);
	virtual ~Bullet();


	SpriteSheet *sprites;
	bool animated = false;
	Animation *frames;
	int x;
	int y;
	int SPEED;
	int speed_elapsed = 0;
};