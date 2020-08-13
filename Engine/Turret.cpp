#include "Turret.h"
# define M_PI           3.14159265358979323846  /* pi */


Turret::Turret(Direction direction, int x, int y, int speed, std::string fileName, std::string bullet_file, int rows, int cols, int width, int height, int lives)
	: Enemy(direction, x, y, speed, fileName, rows, cols, width, height, lives)
{
	bullet = new Bullet(x, y, bullet_file, 1, 1);

}
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
	if (shocked)
	{
		Draw_electric(gfx);
	}
	if (exploded)
	{
		draw_maxs_explosion(gfx);
	}
}

void Turret::Update_bullet(Character &character)
{
	if (is_shooting)
	{
		bullet->x += round(attack_vector->getX());
		bullet->y += round(attack_vector->getY());

		if (bullet->x < 100 || bullet->y < 100 || bullet->x > Graphics::ScreenWidth - 100 || bullet->y > Graphics::ScreenHeight - 100)
		{

			is_shooting = false;
		}
	}

	if (!is_shooting)
	{
		if (nextBool(1))
		{
			attack_degree = GetDegree(x, y, character.GetX(), character.GetY());

			bullet->x = x;
			bullet->y = y;
			//reposition bullet to match turret
			bullet->reposition_gun_bullet(attack_degree, width, height);
			attack_degree = GetDegree(bullet->x, bullet->y, character.GetX(), character.GetY());
			attack_vector = new Vector(attack_degree, 15);
			is_shooting = true;
		}
	}
}

void Turret::Draw_bullet(Graphics &gfx)
{
	if (is_shooting)
	bullet->sheet->drawFrame(gfx, 0, bullet->x, bullet->y);
}


