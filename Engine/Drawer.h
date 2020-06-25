#pragma once

#include "Graphics.h"
#include "Keyboard.h"

class Drawer
{
public:
	static void DrawRectangle(Graphics& gfx, int x, int y, int width, int height, int r, int g, int b);
	void DrawLine(int from, int to, int r, int g, int b);
	void DrawTriangle(int x, int y, int height, int r, int g, int b);
	void DrawBall(int diameter, int r, int g, int b);
};