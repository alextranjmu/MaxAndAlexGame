#include "Thundercloud.h"



Thundercloud::Thundercloud(int x, int y, SpriteSheet *sprites, int direction, double magnitude)
	: Bullet(x, y, sprites, direction, magnitude)
{
	expire_timer = 0;
}

void Thundercloud::update(std::vector<Enemy*> enemies)
{
	expire_timer++;
	if (expire_timer > 21 || expire_timer < 31)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			bool collision = false; // collision logic
			if (collision)
			{

			}
		}
	}
	if (expire_timer == 54)
	{
		expire();
	}
}

Thundercloud::~Thundercloud()
{
}
