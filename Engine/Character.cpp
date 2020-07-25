#include "Character.h"
#include "Graphics.h"

Character::Character()
{
	direction = NO_DIRECTION;
	x = 100;
	y = 100;
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

void Character::Update(const Keyboard & kbd, int x1, int x2, int y1, int y2)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		collisionUpdatexdown(x1, x2, y1, y2);
		x += SPEED;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		collisionUpdatexup(x1, x2, y1, y2);
		x -= SPEED;
	}
	if (kbd.KeyIsPressed(VK_DOWN))
	{
		collisionUpdatexdown(x1, x2, y1, y2);
		y += SPEED;
	}
	if (kbd.KeyIsPressed(VK_UP))
	{
		collisionUpdatexup(x1, x2, y1, y2);
		y -= SPEED;
	}
	if (kbd.KeyIsPressed(VK_SPACE)) {

	}
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


void Character::collisionUpdatexup(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x += SPEED;
	}
}

void Character::collisionUpdatexdown(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x -= SPEED;
	}
}


void Character::collisionUpdateyup(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y += SPEED;
	}
}

void Character::collisionUpdateydown(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y -= SPEED;
	}
}
