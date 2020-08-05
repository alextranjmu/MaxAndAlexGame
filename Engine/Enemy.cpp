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

void Enemy::update(int x1, int x2, int y1, int y2)
{
	
}

void Enemy::Draw(Graphics & gfx)
{
	gfx.drawSurface(x, y, *s);
}


void Enemy::AImove()
{

}

void Enemy::shoot()
{
}

void Enemy::randomMove(vector<Obstacle*>& obstacles, int enemy_width, int enemy_height)
{

	if (nextBool(0.01))
	{
		 direction = static_cast<Direction>(rand() % 4);
	}
	switch (direction)
	{
	case LEFT:
		x -= speed;
		for (int i = 0; i < obstacles.size(); i++)
		{
			collisionUpdatexup(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, enemy_width, enemy_height);
		}		break;
	case RIGHT:
		x += speed;
		for (int i = 0; i < obstacles.size(); i++)
		{
			collisionUpdatexdown(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, enemy_width, enemy_height);
		}		break;
	case UP:
		y -= speed;
		for (int i = 0; i < obstacles.size(); i++)
		{
			collisionUpdateyup(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, enemy_width, enemy_height);
		}		break;
	case DOWN:
		y += speed;
		for (int i = 0; i < obstacles.size(); i++)
		{
			collisionUpdateydown(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, enemy_width, enemy_height);
		}		break;
	case NO_DIRECTION:
		break;
	}
}

void Enemy::clamp_screen()
{
	const int right = x;
	if (x < 0)
	{
		direction = RIGHT;
		x = 0;
	}
	else if (right >(Graphics::ScreenWidth / 3) * 2)
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

bool Enemy::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}


void Enemy::collisionUpdatexup(int x1, int x2, int y1, int y2, int enemy_width, int enemy_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x += speed;
	}
}

void Enemy::collisionUpdatexdown(int x1, int x2, int y1, int y2, int enemy_width, int enemy_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x -= speed;
	}
}


void Enemy::collisionUpdateyup(int x1, int x2, int y1, int y2, int enemy_width, int enemy_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y += speed;
	}
}

void Enemy::collisionUpdateydown(int x1, int x2, int y1, int y2, int enemy_width, int enemy_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y -= speed;
	}
}
