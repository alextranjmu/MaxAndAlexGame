#pragma once

#include <string>
#include "Surface.h"
#include "Graphics.h"

class SpriteSheet
{
public:
	SpriteSheet(std::string fileName, int rows, int columns);
	~SpriteSheet();
	void drawFrame(Graphics& gfx, int frame_num, int x, int y);
	void drawFrameHorizontalFlip(Graphics& gfx, int frame_num, int x, int y);
	int Width();
	int Height();
private:
	int num_frames;
	int frame_width;
	int frame_height;
	Pixel *frames;
};

