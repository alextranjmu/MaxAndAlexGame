#pragma once
#include "Enemy.h"
#include "Bullet.h"
class LazerBot : public Enemy
{
public:
	LazerBot(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives);
	Bullet *left_missile;
	Bullet *right_missile;

	bool is_shooting_left_missile = false;

	bool is_shooting_right_missile = false;

	bool is_drawing_left_missile = false;

	bool is_drawing_right_missile = false;

	void Update_bullet();
	void Draw(Graphics &gfx);
	void Draw_missile(Graphics &gfx);
};