#include "Wizard.h"
#include "Keyboard.h"
#include "Obstacle.h"

Wizard::Wizard(int x2, int y2, char* spritesheet, int ssrows, int sscols, Game *g)
	: Character::Character(x2, y2, spritesheet, ssrows, sscols)
{
	game = g;
	SPEED = 4;
	int idle[1] = { 0 };
	idle_animation = new Animation(-1, 3, 0, 0);
	int walk[6] = { 0, 1, 2, 3, 4, 5 };
	walk_cycle = new Animation(-1, 3, 0, 5);
	int spin[12] = { 6, 7, 8, 9, 10, 11, 10, 11, 10, 11, 10, 11};
	spin_attack = new Animation(10, 3, 12, spin);
	swipe_attack = new Animation(5, 3, 12, 17);
	projectiles = {};
	puddles = {};

	tornado_anime = new Animation(-1, 3, 0, 7);
	tornado_sheet = new SpriteSheet("Tornado.bmp", 4, 2);
	rain_anime = new Animation(-1, 2, 0, 17);
	rain_sheet = new SpriteSheet("Thundercloud.bmp", 6, 3);
	puddle_sheet = new SpriteSheet("Puddle.bmp", 1, 1);
	fireball_anime = new Animation(-1, 3, 0, 3);
	fireball_sheet = new SpriteSheet("Fireball.bmp", 2, 2);


	current_animation = idle_animation;
	lives = 100;
}

void Wizard::Move(const Keyboard & kbd, vector<Obstacle*>& obstacles, int wiz_width, int wiz_height)
{

	if (current_animation->isCancelable())
	{	
		bool noKeyPressed = true;
		if (kbd.KeyIsPressed(VK_RIGHT))
		{
			direction = RIGHT;
			noKeyPressed = false;
			x += SPEED;
			for (int i = 0; i < obstacles.size(); i++) 
			{
				collisionUpdatexdown(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, wiz_width, wiz_height);
			}

			setAnimation(walk_cycle);
			current_animation->nextFrame();
		}
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			direction = LEFT;
			noKeyPressed = false;
			x -= SPEED;
			for (int i = 0; i < obstacles.size(); i++)
			{
				collisionUpdatexup(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, wiz_width, wiz_height);
			}

			setAnimation(walk_cycle);
			current_animation->nextFrame();
		}
		if (kbd.KeyIsPressed(VK_DOWN))
		{
			noKeyPressed = false;
			y += SPEED;
			for (int i = 0; i < obstacles.size(); i++)
			{
				collisionUpdateydown(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, wiz_width, wiz_height);
			}
			setAnimation(walk_cycle);
			current_animation->nextFrame();
		}
		if (kbd.KeyIsPressed(VK_UP))
		{
			noKeyPressed = false;
			y -= SPEED;
			for (int i = 0; i < obstacles.size(); i++)
			{
				collisionUpdateyup(obstacles[i]->x1, obstacles[i]->x2, obstacles[i]->y1, obstacles[i]->y2, wiz_width, wiz_height);
			}
			setAnimation(walk_cycle);
			current_animation->nextFrame();
		}
		if (kbd.KeyIsPressed('Z')) { // tornado
			attack_counter = 0;
			noKeyPressed = false;
			setAnimation(spin_attack);
			tornado_attack(kbd);
		}
		else if (kbd.KeyIsPressed('X')) { // raincloud
			attack_counter = 0;
			noKeyPressed = false;
			setAnimation(spin_attack);
			rain_attack(kbd);
		}
		else if (kbd.KeyIsPressed('C')) { // fireball
			attack_counter = 0;
			noKeyPressed = false;
			setAnimation(swipe_attack);
			fireball_attack(kbd);
		}
		if (noKeyPressed)
		{
			//direction = NO_DIRECTION;
			setAnimation(idle_animation);
		}

	}
	else
	{
		current_animation->nextFrame();
		if (current_attack == FIREBALL)
		{
			fireball_attack(kbd);
		}
		if (current_attack == TORNADO)
		{
			tornado_attack(kbd);
		}
		if (current_attack == RAINCLOUD)
		{
			rain_attack(kbd);
		}
	}

	// update projectiles
	for (int i = projectiles.size() - 1; i >= 0; i--)
	{
		if (projectiles.at(i)->isExpired())
		{
			//delete (projectiles.at(i));
			projectiles.erase(projectiles.begin() + i);
		}
		else
		{
			projectiles.at(i)->update(game->enemies);
		}
	}

	// update puddles
	for (int i = puddles.size() - 1; i >= 0; i--)
	{
		if (puddles.at(i)->expired)
		{
			//delete (projectiles.at(i));
			puddles.erase(puddles.begin() + i);
		}
		else
		{
			puddles.at(i)->doCollision(game->enemies);
		}
	}
}

void Wizard::Draw(Graphics& gfx)
{
	switch (direction)
	{
	case RIGHT:
		sprites->drawFrameHorizontalFlip(gfx, current_animation->getCurrentFrame(), x, y);
		break;
	case LEFT:
		sprites->drawFrame(gfx, current_animation->getCurrentFrame(), x, y);
		break;
	case NO_DIRECTION:
		sprites->drawFrame(gfx, current_animation->getCurrentFrame(), x, y);
		break;
	}
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Draw(gfx);
	}
	for (int i = 0; i < puddles.size(); i++)
	{
		puddles.at(i)->Draw(gfx, puddle_sheet);
	}
}

Wizard::~Wizard()
{
	delete walk_cycle;
	delete spin_attack;
	delete idle_animation;
}

bool Wizard::setAnimation(Animation * anime)
{
	if (current_animation != anime)
	{
		current_animation->reset(); // sets previous animation to frame zero so it doesn't start in the middle when used again
		current_animation = anime;
		return true;
	}
	return false;
}

int Wizard::getAttackDirection(const Keyboard & kbd)
{
	if (kbd.KeyIsPressed(VK_UP)) 
	{
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			return UP_LEFT;
		}
		if (kbd.KeyIsPressed(VK_RIGHT))
		{
			return UP_RIGHT;
		}
		return UP;
	}
	else if (kbd.KeyIsPressed(VK_DOWN)) // else gives up priority
	{
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			return DOWN_LEFT;
		}
		if (kbd.KeyIsPressed(VK_RIGHT))
		{
			return DOWN_RIGHT;
		}
		return DOWN;
	}
	return direction;
}

void Wizard::tornado_attack(const Keyboard & kbd)
{
	current_attack = TORNADO;
	if (attack_counter == 12)
	{
		// spawn tornado using getAttackDirection
		//Bullet *cur_projectile = new Bullet(x, y, tornado_sheet, new Vector(getAttackDirection(kbd), 1));
		projectiles.push_back(new Bullet(x, y, tornado_sheet, getAttackDirection(kbd), 1.0));
		for (int i = 0; i < 10; i++)
		{
			projectiles.at(projectiles.size() - 1)->update(game->enemies);
		}
		projectiles.at(projectiles.size() - 1)->setAnimation(-1, 3, 0, 7);
	}
	// send throw direction to the tornado every time this is called
	attack_counter++;
}

void Wizard::rain_attack(const Keyboard & kbd)
{
	current_attack = RAINCLOUD;
	Bullet *cur_projectile = new Bullet(x, y, rain_sheet, getAttackDirection(kbd), 1.0);
	if (attack_counter == 12)
	{
		// spawn raincloud
		projectiles.push_back(cur_projectile);
		for (int i = 0; i < 20; i++)
		{
			cur_projectile->update(game->enemies);
		}
		cur_projectile->setAnimation(-1, 2, 0, 17);
		cur_projectile->setVector(0.0, 0.0);
	}
	if (attack_counter == 35)
	{
		puddles.push_back(new Puddle(cur_projectile->x, cur_projectile->y + 20));
	}
	attack_counter++;
}

void Wizard::fireball_attack(const Keyboard & kbd)
{
	current_attack = FIREBALL;
	if (attack_counter == 8)
	{
		// spawn fireball
		Bullet *cur_projectile = new Bullet(x, y, fireball_sheet, getAttackDirection(kbd), 4.0);
		projectiles.push_back(cur_projectile);
		for (int i = 0; i < 2; i++)
		{
			cur_projectile->update(game->enemies);
		}
		cur_projectile->setAnimation(-1, 3, 0, 3);
	}
	attack_counter++;
}

void Wizard::collisionUpdatexup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x += SPEED;
	}
}

void Wizard::collisionUpdatexdown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x -= SPEED;
	}
}


void Wizard::collisionUpdateyup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y += SPEED;
	}
}

void Wizard::collisionUpdateydown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y -= SPEED;
	}
}