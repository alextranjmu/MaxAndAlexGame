#pragma once
#include "Obstacle.h"
class Ballbot : public Obstacle
{
public:
	Ballbot(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns);
	
	void Update_Beams();
	void Draw_beams();

};