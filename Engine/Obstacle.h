#pragma once
#include "SpriteSheet.h"
#include "Animation.h"
#include <string>

class Obstacle
{
public:
	Obstacle(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns);
	void setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame); // defaults to no animation
	virtual void update();
	void Draw(Graphics &gfx);
	virtual ~Obstacle();

	int x;
	int y;
	int x1;
	int x2;
	int y1;
	int y2;
	SpriteSheet *sprites;
	Animation *frames;
	bool animated = false;
};