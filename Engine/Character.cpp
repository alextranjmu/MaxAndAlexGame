#include "Character.h"
#include "Graphics.h"

Character::Character()
{
	defaultFrame = new PPM("default_pose.ppm");
	runFrames[0] = new PPM("run_keyframes_1.ppm");
	runFrames[1] = new PPM("run_keyframes_2.ppm");
	runFrames[2] = new PPM("run_keyframes_3.ppm");
	runFrames[3] = new PPM("run_keyframes_4.ppm");
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		delete runFrames[i];
	}
	delete defaultFrame;
}

void Character::ClampToScreen()
{
	
	const int right = x + width;
	if( x < 0 )
	{
		x = 0;
	}
	else if( right >= Graphics::ScreenWidth )
	{
		x = (Graphics::ScreenWidth - 1) - width;
	}

	const int bottom = y + height;
	if( y < 0 )
	{
		y = 0;
	}
	else if( bottom >= Graphics::ScreenHeight )
	{
		y = (Graphics::ScreenHeight - 1) - height;
	}
}

void Character::Draw( Graphics& gfx ) const
{
	for (int row = 0; row < defaultFrame->height; row++)
	{
		for (int col = 0; col < defaultFrame->width; col++)
		{
			Pixel p = (Pixel) *(defaultFrame->pixels + row*width + col);
			gfx.PutPixel(x + col, y + row, p.red, p.blue, p.green);
		}
	}
}

void Character::Update( const Keyboard & kbd )
{
	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		x += speed;
	}
	if( kbd.KeyIsPressed( VK_LEFT ) )
	{
		x -= speed;
	}
	if( kbd.KeyIsPressed( VK_DOWN ) )
	{
		y += speed;
	}
	if( kbd.KeyIsPressed( VK_UP ) )
	{
		y -= speed*3;
	}
	if (kbd.KeyIsPressed(VK_ACCEPT)) {

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

void Character::loseLife()
{
	lives--;
}
