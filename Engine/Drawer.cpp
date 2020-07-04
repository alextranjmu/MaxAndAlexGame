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

void Drawer::DrawPPM(Graphics& gfx, int x, int y, PPM *frame)
{
	for (int row = 0; row < frame->height; row++)
	{
		for (int col = 0; col < frame->width; col++)
		{
			Pixel p = (Pixel) *(frame->pixels + row*frame->width + col);
			if (p.red == -1 && p.blue == -1 && p.green == -1)
			{
				// n word
			}
			else
			{
				gfx.PutPixel(x + col, y + row, p.red, p.green, p.blue);
			}
		}
	}
	gfx.PutPixel(500, 500, 255, 255, 255);
	//delete defaultFrame;
}

void Drawer::DrawPPM_Horizontal_Flip(Graphics& gfx, int x, int y, PPM *frame)
{
	for (int row = 0; row < frame->height; row++)
	{
		for (int col = 0; col < frame->width; col++)
		{
			Pixel p = (Pixel) *(frame->pixels + row*frame->width + col);
			if (p.red == -1 && p.blue == -1 && p.green == -1)
			{
				// n word
			}
			else
			{
				gfx.PutPixel(col - x, y + row, p.red, p.green, p.blue);
			}
		}
	}
	gfx.PutPixel(500, 500, 255, 255, 255);
	//delete defaultFrame;
}