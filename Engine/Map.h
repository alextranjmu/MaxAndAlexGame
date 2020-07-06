#pragma once
#include "PPM.h"
#include "Drawer.h"
class Map {
public:
	Map();
	void Draw(Graphics& gfx) const;
	
private:
	PPM *defaultFrame;

};