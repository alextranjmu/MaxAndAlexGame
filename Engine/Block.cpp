#include "Graphics.h"
#include "Block.h"
#include "Drawer.h"

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

void Block::Draw(Graphics& gfx, int x, int y, int width, int height, int r, int g, int b)
{
	draw.DrawRectangle(gfx, x, y, width, height, r,  g,  b);
}
