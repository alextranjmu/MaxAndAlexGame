#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Drawer.h"
#include <random>
#include <Windows.h>
#include "Block.h"
#include "Character.h"
#include "Surface.h"
#include <time.h>
#include "Bullet.h"
#include "Enemy.h"
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
	bool nextBool(double probability);
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
	Character *cop; // should be a subclass of character (and tbh a subclass of a new class - Player)
	static constexpr int nPoo = 1000;
	bool isStarted = false;
	/********************************/
	Surface *map1;
	Surface *rock;
	Surface *pressenter;
	Surface *ballBot;
	int frame_counter;
	clock_t time_between_frames;
	Bullet *bigredbullet;
	boolean bigredbullet_bool;
	boolean lazer_bullet1;
	boolean lazer_bullet2;
	Enemy *gunbot;
	Enemy *lazerbot;
	Bullet *lazer1; 	
	Bullet *lazer2;
	Bullet *lazer3;



};