#include "TitleScreen.h"


TitleScreen::TitleScreen(int x, int y, char * fileName, int rows, int cols)
{
	this->x = x;
	this->y = y;
	sheet = new SpriteSheet(fileName, rows, cols);
	this->difficulty = none;
}

void TitleScreen::Change_difficulty(int cursor_x, int cursor_y, boolean &isStarted)
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

void TitleScreen::end_screen_select(int cursor_x, int cursor_y, Character &character, boolean &isRe_started, boolean &is_Replay)
{
	if (cursor_y > 179 + 30 && cursor_y < 280 + 30)
	{
		over_button = replay;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			is_Replay = true;
		}
	}
	else if (cursor_y > 280 + 30 && cursor_y < 354 + 30)
	{
		over_button = menu;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isRe_started = true;
		}
	}
	else if (cursor_y > 354 + 30 && cursor_y < 455 + 30)
	{
		over_button = quit;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void TitleScreen::pause_screen_select(int cursor_x, int cursor_y, boolean & is_paused,boolean & isRe_started)
{
	if (cursor_y > 93 + 30 && cursor_y < 168 + 30)
	{
		pause = resume;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			is_paused = false;
		}
	}
	else if (cursor_y > 168 + 30 && cursor_y < 248 + 30)
	{
		pause = menu_pause;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isRe_started = true;
		}
	}
	else if (cursor_y > 248 + 30 && cursor_y < 337 + 30)
	{
		pause = quit_pause;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void TitleScreen::won_screen_select(int cursor_x, int cursor_y, Character & character, boolean & isRe_started, boolean & is_Replay)
{
	if (cursor_y > 99 + 30 && cursor_y < 174 + 30)
	{
		over_button = replay;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			is_Replay = true;
		}
	}
	else if (cursor_y > 174 + 30 && cursor_y < 285 + 30)
	{
		over_button = menu;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			isRe_started = true;
		}
	}
	else if (cursor_y > 285 + 30 && cursor_y < 390 + 30)
	{
		over_button = quit;
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void TitleScreen::Draw_Intro(Graphics& gfx)
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
	 default:
		sheet->drawFrame(gfx, 0, 0, 0);
		break;

	}
	
}

void TitleScreen::Draw_End(Graphics & gfx)
{

	switch (over_button)
	{
	case replay:
		sheet->drawFrame(gfx, 1, x, y);
		break;
	case menu:
		sheet->drawFrame(gfx, 2, x, y);
		break;
	case quit:
		sheet->drawFrame(gfx, 3, x, y);
		break;
	default:
		sheet->drawFrame(gfx, 0, x, y);
		break;
	}
}

void TitleScreen::Draw_Pause(Graphics & gfx)
{

	switch (pause)
	{
	case resume:
		sheet->drawFrame(gfx, 1, x, y);
		break;
	case menu_pause:
		sheet->drawFrame(gfx, 2, x, y);
		break;
	case quit_pause:
		sheet->drawFrame(gfx, 3, x, y);
		break;
	default:
		sheet->drawFrame(gfx, 0, x, y);
		break;
	}
}

void TitleScreen::Draw_Won(Graphics & gfx)
{
	switch (over_button)
	{
	case replay:
		sheet->drawFrame(gfx, 1, x, y);
		break;
	case menu:
		sheet->drawFrame(gfx, 2, x, y);
		break;
	case quit:
		sheet->drawFrame(gfx, 3, x, y);
		break;
	default:
		sheet->drawFrame(gfx, 0, x, y);
		break;
	}
}


