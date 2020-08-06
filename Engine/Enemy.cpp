#include "Enemy.h"
#include "Graphics.h"
#include "Surface.h"
#include <random>
# define M_PI           3.14159265358979323846  /* pi */



Enemy::Enemy(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives)
{
	sheet = new SpriteSheet(fileName, rows, cols);
	anime = new Animation(-1, 8, 0, rows*cols - 1);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speed = speed;
	direction = LEFT;
	this->lives = lives;

}


void Enemy::Draw(Graphics & gfx)
{
	sheet->drawFrame(gfx, anime->getCurrentFrame(), x, y);
	anime->nextFrame();
}



void Enemy::Draw_lazer_bot(Graphics & gfx)
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


void Enemy::Draw_legs(Graphics & gfx)
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

void Enemy::MoveTowardsCharacter()
{
	

	x += round(chase_vector->getX());
	y += round(chase_vector->getY());
	chase_vector->setX(0);
	chase_vector->setY(0);
	/*	gun_bullet->x += round(gunbot->attack_vector->getX());
	gun_bullet->y += round(gunbot->attack_vector->getY());*/
}

//the parameters are screen size
//right is distance from right side
//bottom is distance from bottom
void Enemy::clamp_screen(int left, int right, int top, int bottom)
{
	const int x_clone = x;
	if (x < left)
	{
		direction = RIGHT;
		x = left;
	}
	else if (x_clone >Graphics::ScreenWidth - right)
	{
		direction = LEFT;
		x = Graphics::ScreenWidth - right;
	}

	const int y_clone = y;
	if (y < top)
	{
		direction = DOWN;
		y = top;
	}
	else if (y_clone > Graphics::ScreenHeight - bottom)
	{
		direction = UP;
		y = (Graphics::ScreenHeight - bottom);
	}
}

void Enemy::Update_bullet()
{
}



double Enemy::GetDegree(int a1, int a2, int b1, int b2)
{
	static const double TWOPI = 6.2831853071795865;
	static const double RAD2DEG = 57.2957795130823209;
	double theta = atan2(b2 - a2, b1 - a1);

	/*if (theta < 0.0)
	{
	theta += TWOPI;
	}*/
	return theta;
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
