#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Drawer.h"
#include <random>
#include <Windows.h>
#include "Block.h"
#include "Wizard.h"
#include "Surface.h"
#include <time.h>
#include "SpriteSheet.h"
#include "Animation.h"

//bika
class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawGameOver( int x,int y );
	void DrawTitleScreen( int x,int y );
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Drawer draw;
	Block block;
	Wizard *wizard; // should be a subclass of character (and tbh a subclass of a new class - Player)
	static constexpr int nPoo = 1000;
	bool isStarted = false;
	/********************************/
	Surface *map1;
	Surface *rock;
	Surface *pressenter;

	int frame_counter;
	clock_t time_between_frames;
	SpriteSheet *ss;
	Animation anime;
};