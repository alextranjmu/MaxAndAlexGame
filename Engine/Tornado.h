#pragma once
#include "Bullet.h"

class Tornado :
	public Bullet
{
public:
	Tornado(int x, int y, SpriteSheet *sprites, int direction, double magnitude);
	void update(std::vector<Enemy*> enemies);
	int expire_timer;
	~Tornado();
private:
	//vector<Enemy*> grabbed_enemies = {};
};

