#include "Obstacle.h"
#include "Graphics.h"


Obstacle::Obstacle(int xPos, int yPos)
{
	defaultFrame = new PPM("C:\\Users\\Anh Alexander Tran\\Documents\\ballRobot.ppm");
	//runFrames[0] = new PPM("robotflashing.ppm");

	
	 x = xPos;
	 y = yPos;


}

void Obstacle::Draw(Graphics & gfx) const
{
	Drawer draw;
	draw.DrawPPM(gfx, x, y, defaultFrame);



}
