#include "Bullet.h"
#include "Graphics.h"

Bullet::Bullet(int x, int y, std::string fileName, int rows, int cols)
{
	this->x = x;
	this->y = y;
	sheet = new SpriteSheet(fileName, rows, cols);
}

Bullet::Bullet(int x, int y, SpriteSheet *sprites, int direction, double magnitude)
{
	this->x = x;
	this->y = y;
	sheet = sprites;
	this->direction = direction;
	this->magnitude = magnitude;
}

void Bullet::vector_move_forward()
{
	Vector vector = Vector(direction, magnitude);
	x += vector.getX();
	y += vector.getY();

	if (x > Graphics::ScreenWidth - sheet->Width() || x < 0 
		|| y > Graphics::ScreenHeight - sheet->Height() || y < 0)
	{
		expire();
	}
}

void Bullet::expire()
{
	//x = Graphics::ScreenWidth / 2;
	//y = Graphics::ScreenHeight / 2;
	expired = true;
}

bool Bullet::isExpired() 
{
	return expired;
}

void Bullet::update(std::vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		bool collision = false; // collision code
		if (collision)
		{
			enemies.at(i)->lives -= 20;
		}
	}
	vector_move_forward();
}

void Bullet::setVector(int direction, double magnitude)
{
	this->direction = direction;
	this->magnitude = magnitude;
}

Bullet::~Bullet()
{
	//if (animated)
		//delete anime;
	if (vector != nullptr)
	{
		delete vector;
	}
	else
	{
		delete sheet;
	}
}

void Bullet::Draw(Graphics &gfx)
{
	if (animated)
	{
		sheet->drawFrame(gfx, anime->getCurrentFrame(), x, y);
		anime->nextFrame();
	}
	else
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
}

void Bullet::DrawReverse(Graphics &gfx)
{
	if (animated)
	{
		sheet->drawFrameHorizontalFlip(gfx, anime->getCurrentFrame(), x, y);
		anime->nextFrame();
	}
	else
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
}

void Bullet::setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame)
{
	anime = new Animation(cancelable_start_frame, frame_skips, start_frame, end_frame);
	animated = true;
}

void Bullet::setAnimation(Animation * animation)
{
	anime = animation;
	animated = true;
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
	case 5: //upleft
		break;
	case 6: //upright
		break;
	case 7: //downleft
		break;
	case 8: //downright
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

