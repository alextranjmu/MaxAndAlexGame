#include "Tornado.h"



Tornado::Tornado(int x, int y, SpriteSheet *sprites, int direction, double magnitude)
	: Bullet(x, y, sprites, direction, magnitude)
{
	expire_timer = 0;
}

void Tornado::update(std::vector<Enemy*> enemies)
{
	expire_timer++;
	for (int i = 0; i < enemies.size(); i++)
	{
		
		bool collision = false; // collision logic
		if (collision)
		{

		}
	}
	if (expire_timer == 100)
	{
		expire();
	}
	vector_move_forward();
}

Tornado::~Tornado()
{
}
