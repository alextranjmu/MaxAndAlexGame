#pragma once

#include "Colors.h"
#include "Windows.h"
#include <string>
#include "Pixel.h"

class Surface
{
public:
	Surface(std::string fileName);
	Surface(int width, int height);
	Surface(const Surface&);
	void putPixel(int x, int y, Pixel p);
	Pixel getPixel(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	~Surface();
private:
	Pixel* pPixels = nullptr;
	int width;
	int height;
};

