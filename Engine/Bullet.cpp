#include "Bullet.h"

Bullet::Bullet(int x, int y, std::string fileName)
{
	this->x = x;
	this->y = y;
	sprites = new SpriteSheet(fileName, 1, 1);
	frames = new Animation(-1, -1, -1, -1);
}

Bullet::Bullet(int x, int y, std::string fileName, int rows, int columns)
{
	this->x = x;
	this->y = y;
	sprites = new SpriteSheet(fileName, rows, columns);
	frames = new Animation(-1, -1, -1, -1);
}

Bullet::~Bullet()
{
	delete sprites;
	delete frames;
}

void Bullet::setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame)
{
	frames = new Animation(cancelable_start_frame, frame_skips, start_frame, end_frame);
	animated = true;
}

void Bullet::Draw(Graphics &gfx)
{
	sprites->drawFrame(gfx, 0, x, y);
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

