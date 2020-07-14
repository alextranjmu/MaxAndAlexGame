#include "Bullet.h"

Bullet::Bullet(int X, int Y, std::string fileName)
{
	x = X;
	y = Y;
	s = new Surface(fileName);

}

void Bullet::Draw(Graphics &gfx)
{
	gfx.drawSurface(x, y, *s);
}

void Bullet::Accelerate(int direction, int speed)
{
	SPEED = speed;

	switch (direction)
	{
	case 1://up
		y += SPEED;
	case 2://down
		y -= SPEED;
	case 3://left
		x -= SPEED;
	case 4://right 
		x += SPEED;



	}
}

