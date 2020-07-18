#include "Enemy.h"
#include "Graphics.h"
#include "Surface.h"
#include <random>


Enemy::Enemy(Direction direction, int x, int y, int speed, std::string fileName)
{
	s = new Surface(fileName);
	this->x = x;
	this->y = y;
	this->speed = speed;
	direction = LEFT;
}

void Enemy::Update(int x1, int x2, int y1, int y2)
{
	
}

void Enemy::Draw(Graphics & gfx)
{
	gfx.drawSurface(x, y, *s);
}


void Enemy::AImove()
{

}

void Enemy::randomMove()
{

	if (nextBool(0.01))
	{
		 direction = static_cast<Direction>(rand() % 4);
	}
	switch (direction)
	{
	case LEFT:
		x -= speed;
		break;
	case RIGHT:
		x += speed;
		break;
	case UP:
		y -= speed;
		break;
	case DOWN:
		y += speed;
		break;
	case NO_DIRECTION:
		break;
	}
}

void Enemy::clamp_screen_lazer()
{
	const int right = x;
	if (x < Graphics::ScreenWidth / 3)
	{
		direction = RIGHT;
		x = Graphics::ScreenWidth / 3;
	}
	else if (right > (Graphics::ScreenWidth / 3) * 2)
	{
		direction = LEFT;
		x = ((Graphics::ScreenWidth / 3) * 2);
	}

	const int bottom = y;
	if (y < 0)
	{
		direction = DOWN;
		y = 0;
	}
	else if (bottom > Graphics::ScreenHeight - 100)
	{
		direction = UP;
		y = (Graphics::ScreenHeight - 100);
	}
}

void Enemy::Shoot(botname name)
{
	switch (name)
	{
	case GUNBOT:

		break;
	case LAZERBOT:

		break;
	}
}


bool Enemy::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}


