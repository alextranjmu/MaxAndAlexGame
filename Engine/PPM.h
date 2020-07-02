#pragma once

#include "Pixel.h"
#include <fstream>
#include <exception>
#include <iostream>

// reads and manages ppm files

class PPM
{
public:
	PPM();
	PPM(char* fileName);
	~PPM();
	Pixel* pixels;
	int width;
	int height;
private: 
};

