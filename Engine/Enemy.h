#pragma once
#include "Graphics.h"
#include "Obstacle.h"
#include "Vector.h"
#include <vector>
#include "SpriteSheet.h"
#include "Animation.h"
#include <math.h>
using std::vector;

enum botname
{
	GUNBOT = 0, LAZERBOT = 1
};

enum Direction
{
	LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NO_DIRECTION = 4
};


class Enemy
{
public:
	Enemy::Enemy(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols);
	bool is_shooting_left_missile = false;
	bool is_shooting_right_missile = false;
	Vector *attack_vector;
	double attack_degree;
	int x;
	int y;
	int speed;
	SpriteSheet *sheet;
	Animation *anime;
	Direction direction;
	void Update(int x1, int x2, int y1, int y2);

	void DrawTurret(Graphics &gfx);
	void Draw(Graphics &gfx);
	void Draw_gunbot_Legs(Graphics &gfx);
	void Enemy::randomMove(vector<Obstacle*>& obstacles, int enemy_width, int enemy_height);
	void Enemy::clamp_screen(int left, int right, int top, int bottom)
		void clamp_screen_lazer();
	
	bool nextBool(double probability);
	void Enemy::collisionUpdatexup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void Enemy::collisionUpdatexdown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void Enemy::collisionUpdateyup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void Enemy::collisionUpdateydown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);


};