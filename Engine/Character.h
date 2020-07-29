#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "SpriteSheet.h"
#include "Drawer.h"

class Character
{
public:
	Character();
	Character(int x2, int y2, char* spritesheet, int ssrows, int sscols);
	~Character();
	void ClampToScreen(int width, int height);
	void Draw(Graphics& gfx) const;
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;

protected:
	static int const NO_DIRECTION = 0; //need to update so that UP/DOWN and LEfT/RIGHT aren't mutually exclusive
	static int const UP = 1;
	static int const DOWN = 2;
	static int const LEFT = 3;
	static int const RIGHT = 4;

	int lives = 100;

	int SPEED = 4;

	int width;
	int height;

	int x;
	int y;
	int direction;

	SpriteSheet *sprites;
	

};