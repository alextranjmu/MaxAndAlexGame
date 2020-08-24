#pragma once
#include "Bullet.h"
class Thundercloud :
	public Bullet
{
public:
	Thundercloud(int x, int y, SpriteSheet *sprites, int direction, double magnitude);
	void update(std::vector<Enemy*> enemies);
	~Thundercloud();
};

