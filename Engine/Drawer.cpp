#include "Graphics.h"
#include "Drawer.h"

void Drawer::DrawRectangle(Graphics& gfx, int x, int y, int width, int height, int r, int g, int b)
{
	
	
	/*for (int X = x * Graphics::widthRatio; X < Graphics::widthRatio* (width + x); X++) {
		for (int Y = y * Graphics::heightRatio; Y < Graphics::heightRatio * (height + y); Y++) {
			gfx.PutPixel(X, Y, r, g, b);
		}
	}*/
}

void Drawer::DrawCop(Graphics& gfx, int x, int y)
{
	PPM *defaultFrame = new PPM("default_Pose.ppm");
	for (int row = 0; row < defaultFrame->height; row++)
	{
		for (int col = 0; col < defaultFrame->width; col++)
		{
			Pixel p = (Pixel) *(defaultFrame->pixels + row*defaultFrame->width + col);
			gfx.PutPixel(x + col, y + row, p.red, p.blue, p.green);
		}
	}
	gfx.PutPixel(500, 500, 255, 255, 255);
	//delete defaultFrame;
}