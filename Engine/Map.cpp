#include "Map.h"

void Map::Draw(Graphics & gfx) const
{
	Drawer draw;
	draw.DrawPPM(gfx, 0, 0, defaultFrame);
}
