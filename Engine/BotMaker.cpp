#include "BotMaker.h"

BotMaker::BotMaker(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns)
	: Obstacle(x, y, x1, x2, y1, y2, fileName, rows, columns)
{
	this->x = x;
	this->y = y;
}
void BotMaker::Draw(Graphics & gfx)
{
	if (open)
	{
		sprites->drawFrame(gfx, 3, x, y);
		open = false;
	}
	else
	{
		sprites->drawFrame(gfx, 0, x, y);

	}

	/*if (is_closed)
	{
		sprites->drawFrame(gfx, 0, x, y);
	}
	else if (is_opening)
	{
		if (frames->getCurrentFrame() >= 3)
		{
			is_closed = true;
			is_opening = false;
		}
		sprites->drawFrame(gfx, frames->getCurrentFrame(), x, y);
		frames->nextFrame();

	}*/
}
