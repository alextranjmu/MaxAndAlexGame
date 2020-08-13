#include "BotMaker.h"

BotMaker::BotMaker(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns)
	: Obstacle(x, y, x1, x2, y1, y2, fileName, rows, columns)
{

}
void BotMaker::Draw(Graphics & gfx)
{
	if (is_closed)
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

	}
}
