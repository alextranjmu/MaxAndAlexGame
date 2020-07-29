#include "Character.h"
#include "Graphics.h"

Character::Character()
{
	direction = NO_DIRECTION;
	x = 200;
	y = 200;
	width = 20;
	height = 20;
}

Character::Character(int x2, int y2, char* spritesheet, int ssrows, int sscols)
{
	direction = NO_DIRECTION;
	x = x2;
	y = y2;
	sprites = new SpriteSheet(spritesheet, ssrows, sscols);
}

Character::~Character()
{
	delete sprites;
}

void Character::ClampToScreen(int width, int height)
{

	const int right = x;
	if (x < 0)
	{
		x = 0;
	}
	else if (right > Graphics::ScreenWidth - width)
	{
		x = (Graphics::ScreenWidth - width);
	}

	const int bottom = y;
	if (y < 0)
	{
		y = 0;
	}
	else if (bottom > Graphics::ScreenHeight - height - 10)
	{
		y = (Graphics::ScreenHeight - height - 10);
	}
}

void Character::Draw(Graphics& gfx) const
{

}



int Character::GetX() const
{
	return x;
}

int Character::GetY() const
{
	return y;
}

int Character::GetWidth() const
{
	return width;
}

int Character::GetHeight() const
{
	return height;
}



