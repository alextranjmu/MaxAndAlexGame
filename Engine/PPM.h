#pragma once

#include "Pixel.h"
#include <fstream>
#include <exception>
#include <iostream>

// reads and manages ppm files

class PPM
{
public:
	PPM(char* fileName);
	~PPM();
private: 
	int width;
	Pixel* pixels;
	int height;
};

