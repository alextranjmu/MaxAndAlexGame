#pragma once
#include "Graphics.h"
class LifeBar
{
public:
	LifeBar::LifeBar(int x, int y, int width, int height);
	void Draw(Graphics &gfx);
	
	int pixels_per_life;
	int lives;
	int x;
	int y;
	int originalWidth;
	int width;
	int height;
};