#include "Turret.h"
# define M_PI           3.14159265358979323846  /* pi */

//Turret(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives)
//	: Enemy(direction, x, y, speed, fileName, rows, cols, width, height, lives)
//{
//
//}
void Turret::Draw(Graphics &gfx)
{
	if (attack_degree > 0 && attack_degree < M_PI / 6)
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
	else if (attack_degree > M_PI / 6 && attack_degree < M_PI / 3)
	{
		sheet->drawFrame(gfx, 7, x, y);
	}
	else if (attack_degree > M_PI / 3 && attack_degree < 2 * M_PI / 3)
	{
		sheet->drawFrame(gfx, 6, x, y);
	}
	else if (attack_degree > 2 * M_PI / 3 && attack_degree < 5 * M_PI / 6)
	{
		sheet->drawFrame(gfx, 5, x, y);
	}
	else if (attack_degree < 0 && attack_degree >(-1) * M_PI / 6)
	{
		sheet->drawFrame(gfx, 0, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 6 && attack_degree >(-1) * M_PI / 3)
	{
		sheet->drawFrame(gfx, 1, x, y);
	}
	else if (attack_degree < (-1) * M_PI / 3 && attack_degree >(-1) * 2 * M_PI / 3)
	{
		sheet->drawFrame(gfx, 2, x, y);
	}
	else if (attack_degree < (-1) * 2 * M_PI / 3 && attack_degree >(-1) * 5 * M_PI / 6)
	{
		sheet->drawFrame(gfx, 3, x, y);
	}
	else
	{
		sheet->drawFrame(gfx, 4, x, y);

	}
}
