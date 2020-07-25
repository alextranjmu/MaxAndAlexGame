#pragma once
#include "Character.h"
#include "Animation.h"

class Wizard :
	public Character
{
public:
	Wizard(int x2, int y2, char* spritesheet, int ssrows, int sscols);
	~Wizard();
	void Update(const Keyboard & kbd, int x1, int x2, int y1, int y2);
	void Draw(Graphics &gfx);

private:
	Animation *current_animation;
	Animation *idle_animation;
	Animation *walk_cycle;
	Animation *spin_attack;
	void setAnimation(Animation *anime);
	/*int x;
	int y;*/
};

