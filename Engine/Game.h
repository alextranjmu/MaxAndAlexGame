#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Drawer.h"
#include <random>
#include <windows.h>
#include "Block.h"
#include "Character.h"
#include "Surface.h"
#include <time.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Point.h"
#include "Vector.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Wizard.h"
#include <vector>
#include "Obstacle.h"
#include "TitleScreen.h"
#include "LifeBar.h"
#include "Keyboard.h"
#include <iostream>
#pragma comment(lib,"winmm")

using namespace::std;
using std::vector;

//bika
class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go(boolean &is_retarted);
	void Restart();
	void Replay();
	void Update_when_paused();

private:
	void ComposeFrame();
	bool nextBool(double probability);
	void UpdateModel();
	void UpdateLazer1();
	void UpdateLazer2();
	double GetDegree(int a1, int a2, int b1, int b2);
	
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
	Wizard *shot_wiz;

	Obstacle *ballBot_obstacle;
	Obstacle *beach;
	static constexpr int nPoo = 1000;
	boolean game_won;
	boolean isStarted;
	boolean game_over;
	boolean isRe_started;
	boolean is_Replay;
	boolean paused;
	/********************************/
	Surface *map1;
	Surface *rock;
	Surface *pressenter;
	Surface *ballBot;
	Surface *itsover;
	int frame_counter;
	clock_t time_between_frames;
	Bullet *bigredbullet;
	boolean beam1_bool;
	boolean lazer_bullet1;
	boolean lazer_bullet2;
	boolean gun_bullet_bool;
	boolean wiz_shot_at_bool;
	

	Enemy *gunbot;
	Enemy *lazerbot;
	Enemy *gunbot_legs;
	Enemy *lazerbot_legs;
	Enemy *slug;

	Bullet *lazer1; 	
	Bullet *lazer2;
	Bullet *gun_bullet;

	Point *gun_direction;
	Point *destination;
	Point *startingPoint;
	Point *midpoint;

	SpriteSheet *wiz_sheet; //= new SpriteSheet("Wizard.bmp", 4, 3);
	Animation *wiz_anime;//= new Animation(-1, 3, 0, 5);

	SpriteSheet *beach_sheet;
	Animation *beach_anime;

	SpriteSheet *tree_sheet;
	Animation *tree_anime;

	SpriteSheet *rock_sheet;
	Animation *rock_anime;

	SpriteSheet *flipped_palm_tree_sheet;
	Animation *flipped_palm_tree_anime;

	SpriteSheet *white_wiz_sheet;
	Animation *white_wiz_anime;

	SpriteSheet *turret_sheet;
	Animation *turret_anime;

	SpriteSheet *explosion_sheet;
	Animation *explosion_anime;

	int beam1_height;
	int beam1_width;
	int beam1_hold;
	int beam1_speed;
	//int int_array[6] = { 6,7,8,9,10,11 };

	Vector *gunbot_vec;

	vector<Wizard*> characters;
	vector<Enemy*> enemies;
	vector<Obstacle*> obstacles;
	vector<Bullet*> bullets;

	TitleScreen *intro_screen;
	TitleScreen *end_screen;
	TitleScreen *end_screen_win;
	TitleScreen *pause_screen;

	LifeBar *wiz_life_bar;
	LifeBar *gunbot_life_bar;
	LifeBar *lazerbot_life_bar;

	POINT cursor_point;
	HWND window;
	double slope;
	double c;
	double vec_degree;
	int distance;
	int times_to_divide;
};