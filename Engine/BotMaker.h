#pragma once
#include "Obstacle.h"
#include <queue>
#include "Enemy.h"
#include "LazerBot.h"
using namespace std;
class BotMaker : Obstacle
{
public:
	BotMaker(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns);
	queue<Enemy*> dead_slugs_gunbots;
	queue<LazerBot*> dead_lazer_bots;
	bool is_closed = true;
	bool is_opening = false;
	void Draw(Graphics &gfx);

};