#include "LazerBot.h"
LazerBot::LazerBot(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives)
	: Enemy(direction, x, y, speed, fileName, rows, cols, width, height, lives)
{
	left_missile = new Bullet(0, 0, "lazer.bmp", 1, 1);
	right_missile = new Bullet(0, 0, "lazer.bmp", 1, 1);
}
void LazerBot::Update_bullet()
{
	if (!is_shooting_left_missile)
	{

		if (nextBool(0.05));
		{
			left_missile->x = x - left_missile->sheet->Width();
			left_missile->y = y + 50;
			is_drawing_left_missile = true;
			is_shooting_left_missile = true;
		}
	}

	if (is_shooting_left_missile)
	{
		left_missile->Accelerate(3, 10);
		if (left_missile->x < 70)
		{
			
			is_shooting_left_missile = false;
		}
	}



	if (!is_shooting_right_missile)
	{
		if (nextBool(0.05));
		{
			right_missile->x = x + sheet->Width();
			right_missile->y = y + 50;
			is_drawing_right_missile = true;
			is_shooting_right_missile = true;
		}
	}

	if (is_shooting_right_missile)
	{
		
		right_missile->Accelerate(4, 10);
		if (right_missile->x > Graphics::ScreenWidth - 100)
		{
		
			is_shooting_right_missile = false;
		}
	}

}

void LazerBot::Draw(Graphics & gfx)
{

	if (is_drawing_left_missile)
	{
		sheet->drawFrame(gfx, 2, x, y);
		is_drawing_left_missile = false;

	}
	else if (is_drawing_right_missile)
	{
		sheet->drawFrame(gfx, 3, x, y);
		is_drawing_right_missile = false;

	}
	else if (is_drawing_left_missile && is_drawing_right_missile)
	{
		sheet->drawFrame(gfx, 1, x, y);
		is_drawing_left_missile = false;
		is_drawing_right_missile = false;

	}
	else
	{
		sheet->drawFrame(gfx, 0, x, y);
	}

	if (shocked)
	{
		Draw_electric(gfx);
	}

	if (exploded)
	{
		draw_maxs_explosion(gfx);
	}
}

void LazerBot::Draw_missile(Graphics &gfx)
{
	if (is_shooting_left_missile)
	{
		left_missile->sheet->drawFrame(gfx, 0, left_missile->x, left_missile->y);
	}
	if (is_shooting_right_missile)
	{
		right_missile->sheet->drawFrame(gfx, 0, right_missile->x, right_missile->y);

	}
}