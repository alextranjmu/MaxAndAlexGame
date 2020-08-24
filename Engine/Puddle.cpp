#include "Puddle.h"

	Puddle::Puddle(int x, int y)
	{
		this->x = x;
		this->y = y;
		timer = 0;
		expired = false;
	}

	void Puddle::Draw(Graphics &gfx, SpriteSheet *puddle)
	{
		puddle->drawFrame(gfx, 0, x, y);
	}

	void Puddle::doCollision(vector<Enemy*> enemies)
	{
		if (timer >= 150)
		{
			expired = true;
		}
		if (!expired)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				// check collision
			}
		}
	}