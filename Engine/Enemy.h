#pragma once
#include "Graphics.h"

enum botname
{
	GUNBOT = 0, LAZERBOT = 1
};

enum Direction
{
	LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NO_DIRECTION = 4
};


class Enemy
{
public:
	int x;
	int y;
	int speed;
	Surface *s;
	Direction direction;
	Enemy(Direction direction, int x, int y, int speed, std::string fileName);
	void Update(int x1, int x2, int y1, int y2);

	void Draw(Graphics &gfx);
	void Move();
	void AImove();
	void randomMove();
	void clamp_screen_lazer();
	void Shoot(botname name);
	
	bool nextBool(double probability);
	void Shoot();
	
};