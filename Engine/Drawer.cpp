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
				gfx.PutPixel(x - col + frame->width, y + row, p.red, p.green, p.blue);
			}
		}
	}
}

void Drawer::WriteNumber(Graphics & gfx, int x, int y, int number, Color c)
{
	int current_x = x;
	for (int num = number; num > 0; num = num / 10)
	{
		switch (num % 10) // current digit
		{
		case 0:
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			break;
		case 1:
			gfx.PutPixel(current_x + 2, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			break;
		case 2:
			gfx.PutPixel(current_x - 2, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x - 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			break;
		case 3:
			gfx.PutPixel(current_x - 2, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			break;
		case 4:
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			break;
		case 5:
			gfx.PutPixel(current_x - 2, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			break;
		case 6:
			gfx.PutPixel(current_x - 2, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			gfx.PutPixel(current_x - 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			break;
		case 7:
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			break;
		case 8:
			gfx.PutPixel(current_x - 2, y + 2, c);
			gfx.PutPixel(current_x - 1, y + 2, c);
			gfx.PutPixel(current_x, y + 2, c);
			gfx.PutPixel(current_x + 1, y + 2, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			gfx.PutPixel(current_x - 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			break;
		case 9:
			gfx.PutPixel(current_x - 2, y - 2, c);
			gfx.PutPixel(current_x - 1, y - 2, c);
			gfx.PutPixel(current_x, y - 2, c);
			gfx.PutPixel(current_x + 1, y - 2, c);
			gfx.PutPixel(current_x + 2, y - 2, c);
			gfx.PutPixel(current_x - 2, y - 1, c);
			gfx.PutPixel(current_x + 2, y - 1, c);
			gfx.PutPixel(current_x - 2, y, c);
			gfx.PutPixel(current_x - 1, y, c);
			gfx.PutPixel(current_x, y, c);
			gfx.PutPixel(current_x + 1, y, c);
			gfx.PutPixel(current_x + 2, y, c);
			gfx.PutPixel(current_x + 2, y + 1, c);
			gfx.PutPixel(current_x + 2, y + 2, c);
			break;
		}
		current_x -= 7;
	}
}
