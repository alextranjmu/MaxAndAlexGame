#include "Turret.h"
# define M_PI           3.14159265358979323846  /* pi */


Turret::Turret(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives)
	: Enemy(direction, x, y, speed, fileName, rows, cols, width, height, lives)
{

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
}

void Turret::Update_bullet()
{
	if (is_shooting)
	{
		gun_bullet->x += round(attack_vector->getX());
		gun_bullet->y += round(attack_vector->getY());

		if (gun_bullet->x < 100 || gun_bullet->y < 100 || gun_bullet->x > Graphics::ScreenWidth - 100 || gun_bullet->y > Graphics::ScreenHeight - 100)
		{

			is_shooting = false;
		}
	}

	if (!is_shooting)
	{
		if (nextBool(1))
		{
			gunbot->attack_degree = GetDegree(gunbot->x, gunbot->y, wizard->GetX(), wizard->GetY());

			gun_bullet->x = gunbot->x;
			gun_bullet->y = gunbot->y;
			//reposition bullet to match turret
			gun_bullet->reposition_gun_bullet(gunbot->attack_degree, gunbot->width, gunbot->height);
			gunbot->attack_degree = GetDegree(gun_bullet->x, gun_bullet->y, wizard->GetX(), wizard->GetY());
			gunbot->attack_vector = new Vector(gunbot->attack_degree, 15);
			gun_bullet_bool = true;
		}
	}
}
