#include "Surface.h"
#include <fstream>
#include <cassert>



Surface::Surface(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read((char*)&bmFileHeader, sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read((char*)&bmInfoHeader, sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	pPixels = new Color[width * height];

	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			putPixel(x, y, Color(file.get(), file.get(), file.get()));
		}
		file.seekg(padding, std::ios::cur);
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels( new Color[ width * height ])
{
}

Surface::Surface(const Surface& other)
	:
	Surface( other.getWidth(), other.getHeight() )
{
	int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = other.pPixels[i];
	}
}

void Surface::putPixel(int x, int y, Color p)
{
	pPixels[y * width + x] = p;
}

Color Surface::getPixel(int x, int y) const
{
	return pPixels[y * width + x];
}

int Surface::getWidth() const
{
	return width;
}

int Surface::getHeight() const
{
	return height;
}

Surface::~Surface()
{
	delete [] pPixels; // square brackets because...
	pPixels = nullptr;
}
