#include "TitleScreen.h"

TitleScreen::TitleScreen(int x, int y, char * fileName)
{
	this->x = x;
	this->y = y;
	sheet = new SpriteSheet(fileName, 6, 1);
	animation = new Animation(-1, 0, 0, 0);
	this->difficulty = difficulty;
}

void TitleScreen::Change_difficulty(Difficulty difficulty)
{
	this->difficulty = difficulty;
}

void TitleScreen::Draw(Graphics& gfx)
{
	sheet->drawFrame(gfx, 1, 0, 0);
	
}
