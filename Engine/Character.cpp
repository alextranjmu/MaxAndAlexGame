#include "Character.h"
#include "Graphics.h"

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
	for (int faceWidth = -5; faceWidth <= 5; faceWidth++)
	{
		for (int faceHeight = -5; faceHeight <= 5; faceHeight++)
		gfx.PutPixel(x + faceWidth, y + faceHeight, 239,245, 66);
	}

	for (int eyeWidth = 1; eyeWidth <= 3; eyeWidth++)
	{
		for (int eyeHeight = 1; eyeHeight <= 3; eyeHeight++)
			gfx.PutPixel(x + eyeWidth, y - eyeHeight, 0, 0, 0);
	}

	for (int torsoHeight = 5; torsoHeight < 25; torsoHeight++) {
		for (int torsoWidth = -8; torsoWidth < 8; torsoWidth++) {
			gfx.PutPixel(x + torsoWidth, y + torsoHeight, 66, 90, 245);
		}
	}

	for (int leftLegHeight = 25; leftLegHeight < 40; leftLegHeight++) {
		for (int leftLegWidth = -7; leftLegWidth < -1; leftLegWidth++) {
			gfx.PutPixel(x + leftLegWidth, y + leftLegHeight, 194, 194, 66);
		}
	}

	for (int leftLegHeight = 25; leftLegHeight < 40; leftLegHeight++) {
		for (int leftLegWidth = 1; leftLegWidth < 7; leftLegWidth++) {
			gfx.PutPixel(x + leftLegWidth, y + leftLegHeight, 194, 194, 66);
		}
	}

	for (int sleeveHeight = 10; sleeveHeight < 15; sleeveHeight++) {
		for (int sleeveWidth = 0; sleeveWidth < 5; sleeveWidth++) {
			gfx.PutPixel(x + sleeveWidth, y + sleeveHeight, 66, 90, 245);
		}
	}

	for (int armHeight = 10; armHeight < 15; armHeight++) {
		for (int armWidth = 0; armWidth < 15; armWidth++) {
			gfx.PutPixel(x + armWidth, y + armHeight, 239, 245, 66);
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
