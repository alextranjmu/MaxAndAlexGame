#pragma once
#include "Graphics.h"
#include "Surface.h"

# define M_PI           3.14159265358979323846  /* pi */

class Bullet {
public:
	Bullet(int X, int Y, std::string fileName);
	void Draw(Graphics &gfx);
	void Bullet::DrawReverse(Graphics &gfx);
	void Accelerate(int direction, int speed);
	void Bullet::reposition_gun_bullet(int attack_degree, int width, int height);
		Surface *s;
	int x;
	int y;
	int SPEED;
	int speed_elapsed = 0;


};