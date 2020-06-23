#include "Graphics.h"
#include "Drawer.h"

void Drawer::DrawRectangle(Graphics& gfx, int x, int y, int width, int height, int r, int g, int b)
{

	for (int a = x; a < width; a++) {
		for (int b = y; b < height; b++) {
			gfx.PutPixel(a, b, r, g, b);
		}
	}
}
