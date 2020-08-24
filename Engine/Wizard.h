#pragma once
#include "Character.h"
#include "Animation.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Game.h"
#include <vector>
using std::vector;
class Wizard :
	public Character
{
public:
	double lives;
	Wizard(int x2, int y2, char* spritesheet, int ssrows, int sscols, Game *g);
	~Wizard();
	void Wizard::Move(const Keyboard & kbd, vector<Obstacle*>& obstacles, int wiz_width, int wiz_height);
	void Draw(Graphics &gfx);
	void collisionUpdatexup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdatexdown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdateyup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdateydown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);

private:
	int attack_counter;
	Game *game;

	Animation *current_animation;
	Animation *idle_animation;
	Animation *walk_cycle;
	Animation *spin_attack;
	Animation *swipe_attack;
	bool setAnimation(Animation *anime); // returns true if animation was changed
	int getAttackDirection(const Keyboard & kbd);
	void tornado_attack(const Keyboard & kbd);

	std::vector<Bullet*> projectiles;
	Animation *tornado_anime;
	SpriteSheet *tornado_sheet;
	void rain_attack(const Keyboard & kbd);
	Animation *rain_anime;
	SpriteSheet *rain_sheet;
	void fireball_attack(const Keyboard & kbd);
	Animation *fireball_anime;
	SpriteSheet *fireball_sheet;

	int current_attack = NO_ATTACK;
	static const int NO_ATTACK = -1;
	static const int TORNADO = 0;
	static const int FIREBALL = 1;
	static const int RAINCLOUD = 2;

	SpriteSheet *puddle_sheet;
	class Puddle
	{
	public:
		int x;
		int y;
		int timer;
		bool expired;

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
	};
	std::vector<Puddle*> puddles;
};

