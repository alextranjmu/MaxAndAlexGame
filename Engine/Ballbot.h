#pragma once
#include "Obstacle.h"
class Ballbot : public Obstacle
{
public:
	Ballbot(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns);
	
	void Update_Beams();
	void Draw_beams(Graphics &gfx);
	bool beam1_bool = false;
	bool left_beam_bool = false;
	bool right_beam_bool = false;

	int left_beam_width = 0;
	int left_beam_height = 37;

	int right_beam_width = 800; 
	int right_beam_height = 35;

	int beam1_width = 47;
	int beam1_height = 0;

	int left_beam_hold = 0;
	int left_beam_speed = 15;

	int right_beam_hold = 0;
	int right_beam_speed = 15;

	int beam1_hold = 0;
	int beam1_speed = 15;
};