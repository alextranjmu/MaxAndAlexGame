#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Drawer.h"
class Block 
{
private:
	int x;
	int y;
	Drawer draw;
public:
	int getX();
	int getY();
	void Draw(Graphics& gfx, int x, int y, int width, int height, int r, int g, int b);
};
