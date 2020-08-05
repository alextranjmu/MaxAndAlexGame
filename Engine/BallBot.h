#pragma once
#include "Obstacle.h"
class BallBot :
	public Obstacle
{
public:
	BallBot(int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns);
	void update();
	~BallBot();
private:
	int health = 100;
	const int SHOOT_SPEED = 60; // every 60 frames
};

