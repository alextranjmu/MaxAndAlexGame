#include "Bullet.h"

Bullet::Bullet(int x, int y, std::string fileName)
{
	this->x = x;
	this->y = y;
	s = new Surface(fileName);

}

void Bullet::Draw(Graphics &gfx)
{
	gfx.drawSurface(x, y, *s);
}

void Bullet::DrawReverse(Graphics &gfx)
{
	
}

void Bullet::Accelerate(int direction, int speed)
{
	SPEED = speed;

	switch (direction)
	{
	case 1://up
		y += SPEED;
		break;
	case 2://down
		y -= SPEED;
		break;
	case 3://left
		x -= SPEED;
		break;
	case 4://right
		x += SPEED; 
		break;




	}
}

