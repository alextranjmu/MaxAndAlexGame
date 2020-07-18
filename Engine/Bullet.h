#pragma once
#include "Graphics.h"
#include "Surface.h"


class Bullet {
public:
	Bullet(int X, int Y, std::string fileName);
	void Draw(Graphics &gfx);
	void Bullet::DrawReverse(Graphics &gfx);
	void Accelerate(int direction, int speed);
	Surface *s;
	int x;
	int y;
	int SPEED;
	int speed_elapsed = 0;


};