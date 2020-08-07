#pragma once
#include "Enemy.h"
#include "Character.h"
class Slug : public Enemy {
public:
	Slug(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives);

	double chase_degree;

	Vector *chase_vector;

	void Move_to_character(Character &character);

	void Draw(Graphics &gfx);
	
};