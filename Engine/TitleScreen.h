#pragma once
#include <string.h>
#include "Animation.h"
#include "SpriteSheet.h"
#include "Graphics.h"
#include "Character.h"
enum Difficulty {
	invincible = 0, easy = 1, normal = 2, hard = 3, hardest = 4, none = 5
};

enum game_over_button {
	replay = 0, menu = 1, quit = 2
};
class TitleScreen
{

public:
	int x;
	int y;
	game_over_button over_button;
	Difficulty difficulty;
	Animation *animation;
	SpriteSheet *sheet;
	TitleScreen::TitleScreen(int x, int y, char * fileName, int rows, int cols);
	void Change_difficulty(int cursor_x, int cursor_y, boolean &isStarted);
	void TitleScreen::end_screen_select(int cursor_x, int cursor_y, Character &character, boolean &isRe_started, boolean &is_Replay);
		void Draw_Intro(Graphics &gfx);
	void Draw_End(Graphics &gfx);
	
};