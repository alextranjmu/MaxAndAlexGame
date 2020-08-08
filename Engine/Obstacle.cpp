#include "Obstacle.h"

Obstacle::Obstacle(int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

	sprites = new SpriteSheet(fileName, rows, columns);
	frames = new Animation(-1, -1, -1, -1);
}

void Obstacle::setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame)
{
	frames = new Animation(cancelable_start_frame, frame_skips, start_frame, end_frame);
	animated = true;
}

void Obstacle::Draw(Graphics &gfx)
{
	if (animated)
	{
		frames->nextFrame();
		sprites->drawFrame(gfx, frames->getCurrentFrame(), x1, y1);
	}
	else
	{
		sprites->drawFrame(gfx, 0, x1, y1);
	}
}

Obstacle::~Obstacle()
{
	delete frames;
	delete sprites;
}

void Obstacle::update()
{

}