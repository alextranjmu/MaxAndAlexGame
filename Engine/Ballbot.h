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

	int left_beam_width = this->x + 90;
	int left_beam_width_right = this->x + 90;
	int left_beam_height = 37;
	int left_beam_starting_height = this->y + 80;

	int right_beam_width = this->x + 210; 
	int right_beam_width_left = this->x + 210;
	int right_beam_height = 35;
	int right_beam_starting_height = this->y + 80;

	int beam1_x = this->x + 130;
	int beam1_width = 47;
	int beam1_height = this->y + 130;
	int beam1_unchanged_height = this->y + 130;

	int left_beam_hold = 0;
	int left_beam_speed = 15;

	int right_beam_hold = 0;
	int right_beam_speed = 15;

	int beam1_hold = 0;
	int beam1_speed = 15;
};