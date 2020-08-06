#pragma once
#include "Enemy.h"
#include "Graphics.h"


class Turret : Enemy {
public:
		
	Vector *attack_vector;
	double attack_degree;
	void Draw(Graphics &gfx);

};