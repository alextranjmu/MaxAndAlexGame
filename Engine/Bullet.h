#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Vector.h"
#include "Enemy.h"
#include <vector>

# define M_PI           3.14159265358979323846  /* pi */

class Bullet {
public:
	Bullet(int x, int y, std::string fileName, int rows, int cols);
	Bullet(int x, int y, SpriteSheet *sheet, int direction, double magnitude);
	virtual ~Bullet();

	void Draw(Graphics &gfx);
	void Bullet::DrawReverse(Graphics &gfx);
	void Accelerate(int direction, int speed);
	void Bullet::reposition_gun_bullet(int attack_degree, int width, int height);
	void setAnimation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame);
	void setAnimation(Animation *animation);
	void vector_move_forward();
	void setVector(int direction, double magnitude);
	void expire();
	bool isExpired();
	virtual void update(std::vector<Enemy*> enemies);
	bool Detect_Collision(int x1, int y1, int x1plus, int y1plus, int x2, int y2, int x2plus, int y2plus);

	bool animated = false;
	bool expired = false;
	Vector *vector = nullptr;
	double x;
	double y;
	int SPEED;
	int speed_elapsed = 0;
	SpriteSheet *sheet;
	Animation *anime;

	int direction;
	int expire_timer;
	double magnitude;
};