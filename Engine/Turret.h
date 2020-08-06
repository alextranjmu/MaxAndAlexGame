#pragma once
#include "Enemy.h"
#include "Graphics.h"
#include "Bullet.h"
#include "Character.h"

class Turret : public Enemy {
public:
	Turret(Direction direction, int x, int y, int speed, std::string fileName, std::string bullet_file,int rows, int cols, int width, int height, int lives);

	void Update_everything();

	Bullet *bullet;

	double attack_degree;

	Vector *attack_vector = new Vector(0, 15);

	boolean is_shooting = false;

	void Draw(Graphics &gfx);

	void Update_bullet(Character &character);

	void Draw_bullet(Graphics &gfx);


};