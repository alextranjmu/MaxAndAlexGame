#pragma once
#include <string.h>
#include "Animation.h"
#include "SpriteSheet.h"
#include "Graphics.h"
enum Difficulty {
	invincible = 0, easy = 1, normal = 2, hard = 3, hardest = 4, none = 5
};
class TitleScreen
{

public:
	int x;
	int y;
	Difficulty difficulty;
	Animation *animation;
	SpriteSheet *sheet;
	TitleScreen(int x, int y, char *fileName);
	void TitleScreen::Change_difficulty(int cursor_x, int cursor_y, bool &isStarted);
		void Draw(Graphics &gfx);
	
};