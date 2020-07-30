#include "LifeBar.h"

LifeBar::LifeBar(int x, int y, int width, int height)
{
	this->pixels_per_life = pixels_per_life;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->originalWidth = width;
}

void LifeBar::Draw(Graphics  &gfx)
{
	for (int i = x; i < width + x; i++)
	{
		for (int z = y; z < height + y; z++)
		{
			gfx.PutPixel(i, z, 234, 30, 30);
		}
	}
	for (int i = x; i < originalWidth + x; i++)
	{
		gfx.PutPixel(i, y, 0, 0, 0);
	}
	for (int i = x; i < originalWidth + x; i++)
	{
		gfx.PutPixel(i, y + height, 0, 0, 0);
	}
	for (int i = y; i < height + y; i++)
	{
		gfx.PutPixel(x, i, 0, 0, 0);
	}
	for (int i = y ; i < height + y; i++)
	{
		gfx.PutPixel(x + originalWidth, i, 0, 0, 0);
	}
	
}
