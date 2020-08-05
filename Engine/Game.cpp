
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <windows.h>
#include "Block.h"
#include "Graphics.h"
#include <cmath>
#include <vector>


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),

	xDist( 0,770 ),
	yDist( 0,570 )
	
{
	frame_counter = 0;
	time_between_frames = clock(); // makes the first measure inaccurate, fuck it though

	wizard = new Wizard(200, 200, "Wizard.bmp", 4, 3);
	shot_wiz = new Wizard(200, 200, "Wiz_shot.bmp", 4, 3);
	std::uniform_int_distribution<int> vDist(-1, 1);
	rock = new Surface("fatrock24.bmp");
	map1 = new Surface("map1.bmp");
	pressenter = new Surface("pressenter.bmp");
	ballBot_obstacle = new Obstacle(600, 800, 350, 500, "ballRobot24.bmp", 1, 1);
	bigredbullet = new Bullet(735, 400, "bigredbullet24.bmp");
	itsover = new Surface("pressenter.bmp");
	beam1_bool = false;
	lazer_bullet1 = false;
	lazer_bullet2 = false;
	gunbot = new Enemy(LEFT, 600, 300,5, "gunbot.bmp");
	lazerbot = new Enemy(LEFT, 400, 300,2, "lazerbot.bmp");
	lazer1 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");
	lazer2 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");
	gun_bullet = new Bullet(0, 0, "bigredbullet24.bmp");
	gunbot_vec = new Vector(0, 15);
	game_over = false;
	wiz_shot_at_bool = false;


	beam1_width = 47;
	beam1_height = 0;
	beam1_hold = 0;
	beam1_speed = 30;
	 
	wiz_sheet = new SpriteSheet("Wizard.bmp", 4, 3);
	wiz_anime = new Animation(-1, 3, 6, 11);

	white_wiz_sheet = new SpriteSheet("Wiz_shot.bmp", 4, 3);
	white_wiz_anime = new Animation(-1, 3, 6, 11);

	beach_sheet = new SpriteSheet("beach.bmp", 5, 1);
	beach_anime = new Animation(-1, 8, 0, 4);

	tree_sheet = new SpriteSheet("palmtree.bmp", 2, 2);
	tree_anime = new Animation(-1, 8, 0, 3);

	rock_sheet = new SpriteSheet("rock.bmp", 1, 1);
	rock_anime = new Animation(-1, 0, 0, 0);

	flipped_palm_tree_sheet = new SpriteSheet("flipped_palm_tree.bmp", 2, 2);
	flipped_palm_tree_anime = new Animation(-1, 8, 0, 3);

	turret_sheet = new SpriteSheet("turret.bmp", 4, 2);
	turret_anime = new Animation(-1, 8, 0, 7);

	intro_screen = new TitleScreen(0, 0, "titlescreen.bmp", 6, 1);
	end_screen = new TitleScreen(0, 0, "end_screen.bmp", 2, 2);
	end_screen_win = new TitleScreen(0, 0, "end_screen_win.bmp", 2, 2);
	pause_screen = new TitleScreen(0, 0, "pause_screen.bmp", 2, 2);
	
	//THEM LISTS FOR YOU MAX
	characters.push_back(wizard);
	characters.push_back(shot_wiz);
	enemies.push_back(gunbot);
	enemies.push_back(lazerbot);
	obstacles.push_back(ballBot_obstacle);
	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if( isStarted)
	{
		for (int i = 0; i < characters.size(); i++)
		{
			characters[i]->Move(wnd.kbd, obstacles, wiz_sheet->Width(), wiz_sheet->Height());
			characters[i]->ClampToScreen(wiz_sheet->Width(), wiz_sheet->Height());
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->randomMove(obstacles, 0,0);
		}
		

	}
	else
	{

		if( wnd.kbd.KeyIsPressed( VK_RETURN) )
		{
			isStarted = true;
		}
	}

	if (beam1_bool)
	{
		beam1_height -= beam1_speed;
		if (beam1_height <= 0)
		{
			beam1_height = 0;
			beam1_speed = 0;
			beam1_hold += 1;
			if (beam1_hold == 200)
			{
				beam1_height = 450;
				beam1_hold = 0;
				beam1_bool = false;
			}
		}
	}

	if (!beam1_bool)
	{
		if (nextBool(0.05))
		{
			beam1_speed = 50;
			beam1_bool = true;
		}
	}


	if (!lazer_bullet1)
	{
		if (nextBool(0.05));
		{
			
			lazer_bullet1 = true;
		}
	}

	if (lazer_bullet1)
	{
		lazer1->Accelerate(3, 3);
		if (lazer1->x < 70)
		{
			lazer1->x = lazerbot->x - lazer1->sprites->Width();
			lazer1->y = lazerbot->y + 20;
			lazer_bullet1 = false;
		}
	}

	

	if (lazer_bullet2)
	{
		lazer2->Accelerate(4, 3);
		if (lazer2->x > Graphics::ScreenWidth - 100)
		{
			lazer_bullet2 = false;
		}
	}

	if (!lazer_bullet2)
	{
		if (nextBool(0.05))
		{
			lazer2->x = lazerbot->x + lazerbot->s->getWidth();
			lazer2->y = lazerbot->y + 20;
			lazer_bullet2 = true;
		}
	}

	if (gun_bullet_bool)
	{
		gun_bullet->x += round(gunbot_vec->getX());
		gun_bullet->y += round(gunbot_vec->getY());

		if (gun_bullet->x < 100 || gun_bullet->y < 100 || gun_bullet->x > Graphics::ScreenWidth - 100 || gun_bullet->y > Graphics::ScreenHeight - 100)
		{

			gun_bullet_bool = false;
		}
	}

	if (!gun_bullet_bool)
	{
		if (nextBool(1))
		{
			vec_degree = GetDegree(gunbot->x, gunbot->y, wizard->GetX() + 50, wizard->GetY() + 50);
			gunbot_vec = new Vector(vec_degree, 15);
			gun_bullet->x = gunbot->x;
			gun_bullet->y = gunbot->y;
			gun_bullet_bool = true;
		}
	}

	//COLLISION CHUNGUS
	int wiz_x = wizard->GetX();
	int wiz_y = wizard->GetY();
	int bullet_x = gun_bullet->x;
	int bullet_y = gun_bullet->y;
	int lazer1_x = lazer1->x;
	int lazer1_y = lazer1->y;
	int lazer2_x = lazer2->x;
	int lazer2_y = lazer2->y;
	wiz_shot_at_bool = false;
	



	if ((wiz_x < bullet_x + gun_bullet->sprites->Width()) && (wiz_y < bullet_y + gun_bullet->sprites->Height())
		&& ((wiz_x + wiz_sheet->Width() > bullet_x) && (wiz_y < bullet_y + gun_bullet->sprites->Height()))
		&& ((wiz_x < bullet_x + gun_bullet->sprites->Width()) && (wiz_y + wiz_sheet->Height() > bullet_y))
		&& ((wiz_x + wiz_sheet->Width() > bullet_x) && (wiz_y + wiz_sheet->Height() > bullet_y))
		)
	{
		wiz_shot_at_bool = true;
	}

	if((wiz_x < lazer1_x + lazer1->sprites->Width()) && (wiz_y < lazer1_y + lazer1->sprites->Height())
		&& ((wiz_x + wiz_sheet->Width() > lazer1_x) && (wiz_y < lazer1_y + lazer1->sprites->Height()))
		&& ((wiz_x < lazer1_x + lazer1->sprites->Width()) && (wiz_y + wiz_sheet->Height() > lazer1_y))
		&& ((wiz_x + wiz_sheet->Width() > lazer1_x) && (wiz_y + wiz_sheet->Height() > lazer1_y))
		)
	{
		wiz_shot_at_bool = true;
	}

	if ((wiz_x < lazer2_x + lazer1->sprites->Width()) && (wiz_y < lazer2_y + lazer1->sprites->Height())
		&& ((wiz_x + wiz_sheet->Width() > lazer2_x) && (wiz_y < lazer2_y + lazer1->sprites->Height()))
		&& ((wiz_x < lazer2_x + lazer1->sprites->Width()) && (wiz_y + wiz_sheet->Height() > lazer2_y))
		&& ((wiz_x + wiz_sheet->Width() > lazer2_x) && (wiz_y + wiz_sheet->Height() > lazer2_y))
		)
	{
		wiz_shot_at_bool = true;
	}

	if (((wiz_x < 730 + beam1_width && wiz_x > 730) || (wiz_x + wiz_sheet->Width() > 730 && wiz_x + wiz_sheet->Width() < 730 + beam1_width) 
		|| (wiz_x +wiz_sheet->Width()/2 < 730 + beam1_width && wiz_x + wiz_sheet->Width() / 2 > 730))
		&& beam1_height < wiz_y)
	{
		wiz_shot_at_bool = true;
	}


	
	
	
	
	
	gunbot->clamp_screen();
	lazerbot->clamp_screen();
	
}

void Game::DrawGameOver(int x, int y) 
{
	gfx.drawSurface(0, 0, *itsover);
}





void Game::ComposeFrame()
{
	if (isStarted)
	{
		beach_sheet->drawFrame(gfx, beach_anime->getCurrentFrame(), 0, 0);
		beach_anime->nextFrame();

		tree_sheet->drawFrame(gfx, tree_anime->getCurrentFrame(), 48, 300);
		tree_anime->nextFrame();

		flipped_palm_tree_sheet->drawFrame(gfx, flipped_palm_tree_anime->getCurrentFrame(), 100, 350);
		flipped_palm_tree_anime->nextFrame();

		tree_sheet->drawFrame(gfx, tree_anime->getCurrentFrame(), 50, 400);
		tree_anime->nextFrame();

		
		

		wizard->Draw(gfx);
		
		gunbot->Draw(gfx);

		lazerbot->Draw(gfx);

		

		ballBot_obstacle->Draw(gfx);


		if (beam1_bool)
		{
			int tempX = 730 + beam1_width / 6;
			int x = 730;
			for (; x < beam1_width + 730; x++)
			{
				for (int y = 450; y > beam1_height; y--)
				{
					gfx.PutPixel(x, y, 222, 34, 34);
				}
			}
			


		}

		time_between_frames = clock() - time_between_frames;
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 10, 10, time_between_frames, Color(0, 0, 0));
		time_between_frames = clock();
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 50, 10, ++frame_counter, Color(0, 0, 0));
		

		if (lazer_bullet1)
		{
			lazer1->Draw(gfx);
		}

		if (lazer_bullet2)
		{
			lazer2->Draw(gfx);
		}
		
		if (gun_bullet_bool)
		{
			
			gun_bullet->Draw(gfx);
		}
		rock_sheet->drawFrame(gfx, 0, 400, 400);


		if (game_over)
		{
			//gfx.drawSurface(0, 0, *pressenter);

		}
	}
	else 
	{
		for (int x = 0; x < Graphics::ScreenWidth; x++) {
			for (int y = 0; y < Graphics::ScreenHeight; y++) {
				gfx.PutPixel(x, y, 255, 255, 255);
			}
		}
		//Surface *pressenter = new Surface("pressenter.bmp");
		gfx.drawSurface(0, 0, *pressenter);

		time_between_frames = clock() - time_between_frames;
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 10, 10, time_between_frames, Color(0, 0, 0));
		time_between_frames = clock();
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 50, 10, ++frame_counter, Color(0, 0, 0));
	}

	if (wiz_shot_at_bool)
	{

		shot_wiz->Draw(gfx);
	}


}

bool Game::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}



double Game::GetDegree(double a1, double a2, double b1, double b2)
{
	static const double TWOPI = 6.2831853071795865;
	static const double RAD2DEG = 57.2957795130823209;
	double theta = atan2(b2 - a2, b1 - a1);
	
	/*if (theta < 0.0)
	{
		theta += TWOPI;
	}*/
	return theta  ;
}

//DONT LOOK INSIDE THIS FUNCTION 
void Game::Restart()
{
	paused = false;
	isRe_started = false;
	is_Replay = false;
	isStarted = false;
	game_over = false;
	frame_counter = 0;
	time_between_frames = clock(); // makes the first measure inaccurate, fuck it though
								   //window = wnd.hWnd;
	wizard = new Wizard(200, 200, "Wizard.bmp", 4, 3);
	shot_wiz = new Wizard(200, 200, "Wiz_shot.bmp", 4, 3);

	std::uniform_int_distribution<int> vDist(-1, 1);

	rock = new Surface("fatrock24.bmp");
	map1 = new Surface("map1.bmp");

	ballBot = new Surface("ballRobot24.bmp");
	ballBot_obstacle = new Obstacle(600, 800, 350, 500);

	beach = new Obstacle(0, 1120, 0, 100);

	//bigredbullet = new Bullet(735, 400, "bigredbullet24.bmp");
	//itsover = new Surface("pressenter.bmp");

	beam1_bool = false;

	lazer_bullet1 = false;

	lazer_bullet2 = false;

	gunbot = new Enemy(LEFT, 600, 300, 1, "gunbot.bmp", 4, 2, 55, 55, 10);
	gunbot_legs = new Enemy(LEFT, 600, 300, 1, "gunbot_legs.bmp", 3, 1, 55, 55, 100);

	lazerbot = new Enemy(LEFT, 400, 300, 2, "lazerbot.bmp", 2, 2, 0, 0, 10);
	lazerbot_legs = new Enemy(LEFT, 400, 300, 2, "lazerbot_legs.bmp", 2, 1, 0, 0, 10);

	slug = new Enemy(LEFT, 500, 200, 1, "slug.bmp", 5, 1, 0, 0, 10);
	slug->chase_vector = new Vector(0, 5);


	lazer1 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");//left missile
	lazer2 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");//right missile

	gun_bullet = new Bullet(0, 0, "bigredbullet24.bmp");//red ball
	gunbot->attack_vector = new Vector(0, 15);

	game_over = false;

	wiz_shot_at_bool = false;

	intro_screen = new TitleScreen(0, 0, "titlescreen.bmp", 6, 1);
	end_screen = new TitleScreen(0, 0, "end_screen.bmp", 2, 2);
	end_screen_win = new TitleScreen(0, 0, "end_screen_win.bmp", 2, 2);

	wiz_life_bar = new LifeBar(wizard->GetX(), wizard->GetY(), wizard->lives, 15);

	beam1_width = 47;
	beam1_height = 0;
	beam1_hold = 0;
	beam1_speed = 30;

	wiz_sheet = new SpriteSheet("Wizard.bmp", 4, 3);
	wiz_anime = new Animation(-1, 3, 6, 11);

	white_wiz_sheet = new SpriteSheet("Wiz_shot.bmp", 4, 3);
	white_wiz_anime = new Animation(-1, 3, 6, 11);

	beach_sheet = new SpriteSheet("beach.bmp", 5, 1);
	beach_anime = new Animation(-1, 8, 0, 4);

	tree_sheet = new SpriteSheet("palmtree.bmp", 2, 2);
	tree_anime = new Animation(-1, 8, 0, 3);

	rock_sheet = new SpriteSheet("rock.bmp", 1, 1);
	rock_anime = new Animation(-1, 0, 0, 0);

	flipped_palm_tree_sheet = new SpriteSheet("flipped_palm_tree.bmp", 2, 2);
	flipped_palm_tree_anime = new Animation(-1, 8, 0, 3);

	turret_sheet = new SpriteSheet("turret.bmp", 4, 2);
	turret_anime = new Animation(-1, 8, 0, 7);

	explosion_sheet = new SpriteSheet("explosion.bmp", 4, 3);
	explosion_anime = new Animation(-1, 8, 0, 11);



	//THEM LISTS FOR YOU MAX
	characters.push_back(wizard);
	characters.push_back(shot_wiz);

	enemies.push_back(gunbot);
	enemies.push_back(lazerbot);


	obstacles.push_back(ballBot_obstacle);
	obstacles.push_back(beach);
}

void Game::Replay()
{
	Restart();
	isStarted = true;
}

void Game::Update_when_paused()
{
	pause_screen->pause_screen_select(cursor_point.x, cursor_point.y, paused, isRe_started);
}

