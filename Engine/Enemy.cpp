#include "Enemy.h"
#include "Graphics.h"
#include "Surface.h"
#include <random>
# define M_PI           3.14159265358979323846  /* pi */



Enemy::Enemy(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols)
{
	sheet = new SpriteSheet(fileName, rows, cols);
	anime = new Animation(-1, 8, 0, 2);
	this->x = x;
	this->y = y;
	this->speed = speed;
	direction = LEFT;
}


void Enemy::DrawTurret(Graphics & gfx)
{
	//sheet->drawFrame(gfx, 0, x, y);
	//sheet->drawFrame(gfx, 3, x, y);
	if (attack_degree < 0)
	{
		//attack_degree *= -1;
	}
	if (attack_degree > 0 && attack_degree < M_PI / 6)
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
	else if (attack_degree > M_PI / 6 && attack_degree < M_PI / 3)
	{
		sheet->drawFrame(gfx, 7, x, y);
	}
	else if (attack_degree > M_PI / 3 && attack_degree < 2 * M_PI / 3)
	{
		sheet->drawFrame(gfx, 6, x, y);
	}
	else if (attack_degree > 2 * M_PI / 3 && attack_degree < 5 * M_PI / 6)
	{
		sheet->drawFrame(gfx, 5, x, y);
	}
	else if (attack_degree < 0 && attack_degree >(-1) * M_PI / 6)
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 6 && attack_degree >(-1) * M_PI / 3)
	{
		sheet->drawFrame(gfx, 1, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 3 && attack_degree >(-1) * 2 * M_PI / 3)
	{
		sheet->drawFrame(gfx, 2, x, y);
	}
	else if (attack_degree < (-1) * 2 * M_PI / 3 && attack_degree >(-1) * 5 * M_PI / 6)
	{
		sheet->drawFrame(gfx, 3, x, y);
	}
	else
	{
		sheet->drawFrame(gfx, 4, x, y);

	}
}

void Enemy::Draw(Graphics & gfx)
{
	if (is_shooting_left_missile)
	{
		sheet->drawFrame(gfx, 2, x, y);
	}
	else if (is_shooting_right_missile)
	{
		sheet->drawFrame(gfx, 3, x, y);
	}
	else if (is_shooting_left_missile && is_shooting_right_missile)
	{
		sheet->drawFrame(gfx, 1, x, y);
	}
	else
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
	
}

void Enemy::Draw_gunbot_Legs(Graphics & gfx)
{
	sheet->drawFrame(gfx, anime->getCurrentFrame(), x, y);
	anime->nextFrame();
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
