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

void Bullet::reposition_gun_bullet(int attack_degree, int width, int height)
{
	
	if (attack_degree > 0 && attack_degree < M_PI / 6)
	{
		y += height / 2;
		x += width;
	}
	else if (attack_degree > M_PI / 6 && attack_degree < M_PI / 3)
	{
		x += width;
		y += height;
		//sheet->drawFrame(gfx, 7, x, y);
	}
	else if (attack_degree > M_PI / 3 && attack_degree < 2 * M_PI / 3)
	{
		x += width / 2 ;
		y += height;
		//sheet->drawFrame(gfx, 6, x, y);
	}
	else if (attack_degree > 2 * M_PI / 3 && attack_degree < 5 * M_PI / 6)
	{
		//y += height/2;
		//sheet->drawFrame(gfx, 5, x, y);
	}
	else if (attack_degree < 0 && attack_degree >(-1) * M_PI / 6)
	{
		y += height / 2;
		x += width;
		//sheet->drawFrame(gfx, 0, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 6 && attack_degree >(-1) * M_PI / 3)
	{
		x += width;
		//sheet->drawFrame(gfx, 1, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 3 && attack_degree >(-1) * 2 * M_PI / 3)
	{
		x += width / 2;
		//sheet->drawFrame(gfx, 2, x, y);
	}
	else if (attack_degree < (-1) * 2 * M_PI / 3 && attack_degree >(-1) * 5 * M_PI / 6)
	{
		x += width / 2;
		//sheet->drawFrame(gfx, 3, x, y);
	}
	else
	{
		y += height / 2;
		//sheet->drawFrame(gfx, 4, x, y);

	}
}

