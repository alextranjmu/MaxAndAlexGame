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
	Enemy::Enemy(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives);
	bool is_shooting_left_missile = false;
	bool is_shooting_right_missile = false;
	bool death = false;
	bool exploded = false;
	int explode_max_frame_count = 3;
	Vector *chase_vector;
	double chase_degree;
	int x;
	int y;
	int speed;
	int width;
	int height;
	int lives;

	SpriteSheet *sheet;
	Animation *anime;
	Direction direction;
	void Update(int x1, int x2, int y1, int y2);
	
	virtual void Draw(Graphics & gfx);
	void Draw_lazer_bot(Graphics & gfx);
	void Draw_legs(Graphics & gfx);
	void randomMove(vector<Obstacle*>& obstacles, int enemy_width, int enemy_height);
	void MoveTowardsCharacter();
	void clamp_screen(int left, int right, int top, int bottom);
	virtual void shoot();

	double GetDegree(int a1, int a2, int b1, int b2);
	
	bool nextBool(double probability);
	void collisionUpdatexup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdatexdown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdateyup(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);
	void collisionUpdateydown(int x1, int x2, int y1, int y2, int wiz_width, int wiz_height);


};