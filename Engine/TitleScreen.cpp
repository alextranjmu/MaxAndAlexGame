#include "TitleScreen.h"

TitleScreen::TitleScreen(int x, int y, char * fileName)
{
	this->x = x;
	this->y = y;
	sheet = new SpriteSheet(fileName, 6, 1);
	animation = new Animation(-1, 0, 0, 0);
	this->difficulty = none;
}

void TitleScreen::Change_difficulty(int cursor_x, int cursor_y, bool& isStarted)
{
	if (cursor_y > 155 && cursor_y < 203)
	{
		this->difficulty = invincible;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	else if (cursor_y > 203+30 && cursor_y < 238+30)
	{
		this->difficulty = easy;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	else if (cursor_y > 238+30 && cursor_y < 274+30)
	{
		this->difficulty = normal;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	else if (cursor_y > 274+30 && cursor_y < 308+30)
	{
		this->difficulty = hard;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	else if (cursor_y > 308+30 && cursor_y < 367+30)
	{
		this->difficulty = hardest;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	else
	{
		this->difficulty = none;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isStarted = true;
		}
	}
	
}

void TitleScreen::Draw(Graphics& gfx)
{
	switch (difficulty)
	{
	case invincible:
		sheet->drawFrame(gfx, 5, 0, 0);
		break;
	case easy:
		sheet->drawFrame(gfx, 4, 0, 0);
		break;
	case normal:
		sheet->drawFrame(gfx, 3, 0, 0);
		break;
	case hard:
		sheet->drawFrame(gfx, 2, 0, 0);
		break;
	case hardest:
		sheet->drawFrame(gfx, 1, 0, 0);
		break;
	case none:
		sheet->drawFrame(gfx, 0, 0, 0);
		break;

	}
	
}
