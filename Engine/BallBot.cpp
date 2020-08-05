#include "BallBot.h"



BallBot::BallBot(int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns)
	: Obstacle(x1, x2, y1, y2, fileName, rows, columns)
{

}

void BallBot::update()
{
	// shoot lazer
}

BallBot::~BallBot()
{
	// delete objects and free memory
}
