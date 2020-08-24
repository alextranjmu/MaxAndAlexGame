#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include "Enemy.h"
#include <vector>

class Puddle
{
public:
	int x;
	int y;
	int timer;
	bool expired;

	Puddle(int x, int y);
	void Draw(Graphics &gfx, SpriteSheet *puddle);
	void doCollision(std::vector<Enemy*> enemies);
};

