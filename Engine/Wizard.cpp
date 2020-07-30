#include "Wizard.h"
#include "Keyboard.h"
#include "Obstacle.h"




Wizard::Wizard(int x2, int y2, char* spritesheet, int ssrows, int sscols)
	: Character::Character(x2, y2, spritesheet, ssrows, sscols)
{
	SPEED = 4;
	int idle[1] = { 0 };
	idle_animation = new Animation(-1, 3, 0, 0);
	int walk[6] = { 0, 1, 2, 3, 4, 5 };
	walk_cycle = new Animation(-1, 3, 0, 5);
	int spin[6] = { 6, 7, 8, 9, 10, 11 };
	spin_attack = new Animation(-1, 3, 6, 11);

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
		if (kbd.KeyIsPressed(VK_SPACE)) {
			noKeyPressed = false;
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
}

Wizard::~Wizard()
{
	delete walk_cycle;
	delete spin_attack;
	delete idle_animation;
}

void Wizard::setAnimation(Animation * anime)
{
	if (current_animation != anime)
	{
		current_animation->reset(); // sets previous animation to frame zero so it doesn't start in the middle when used again
		current_animation = anime;
	}
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