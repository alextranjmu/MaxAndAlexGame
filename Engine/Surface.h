#pragma once

#include "Colors.h"
#include "Windows.h"
#include <string>

class Surface
{
public:
	Surface(std::string fileName);
	Surface(int width, int height);
	Surface(const Surface&);
	void putPixel(int x, int y, Color p);
	Color getPixel(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	~Surface();
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};

