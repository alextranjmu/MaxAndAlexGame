
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <windows.h>
#include "Block.h"
#include "Graphics.h"
#include <cmath>
#include <vector>
#pragma comment(lib,"winmm")


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),

	xDist( 0,770 ),
	yDist( 0,570 )
	
{
	Restart();
}

void Game::Go(boolean &is_restarted)
{
	gfx.BeginFrame();	

	if (!paused && wnd.kbd.KeyIsPressed(VK_BACK))
	{
		paused = true;
	}

	if (!paused)
	{
		UpdateModel();
	}
	if (paused)
	{
		Update_when_paused();
	}
	if (paused && isRe_started)
	{
		Restart();
		paused = false;
		isRe_started = false;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wizard->lives <= 0)
	{
		game_over = true;
	}
	
	if (game_over)
	{
		GetCursorPos(&cursor_point);
		ScreenToClient(wnd.hWnd, &cursor_point);
		end_screen->end_screen_select(cursor_point.x, cursor_point.y, *wizard, isRe_started, is_Replay);
		if (isRe_started)
		{
			Restart();
			isRe_started = false;
		}

		if (is_Replay)
		{
			Replay();
			is_Replay = false;
		}
	

	}

	else if( isStarted && !game_over)
	{
		//MOVE AND CLAMP
		for (int i = 0; i < characters.size(); i++)
		{
			characters[i]->Move(wnd.kbd, obstacles, wiz_sheet->Width(), wiz_sheet->Height());
			characters[i]->ClampToScreen(wiz_sheet->Width(), wiz_sheet->Height());
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->randomMove(obstacles, 0,0);
		}
		gunbot->clamp_screen(100, 100, 100, 150);
		lazerbot->clamp_screen(150, 150, 150, 150);

		//LEGS CODE
		gunbot_legs->x = gunbot->x;
		gunbot_legs->y = gunbot->y;

		lazerbot_legs->x = lazerbot->x;
		lazerbot_legs->y = lazerbot->y;

		//LIFEBAR CODE
		wiz_life_bar->width = round(wizard->lives);
		wiz_life_bar->x = wizard->GetX();
		wiz_life_bar->y = wizard->GetY();


		//ATTACK CODE
		slug->Move_to_character(*wizard);
		gunbot->Update_bullet(*wizard);
		lazerbot->Update_bullet();
		//ballbot->Update_Beams();



		//if (beam1_bool)
		//{
		//	beam1_height -= beam1_speed;
		//	//bigredbullet->Accelerate(2, 10);
		//	//if (bigredbullet->y == 0)
		//	//{
		//	//	bigredbullet->x = 735;
		//	//	bigredbullet->y = 400;
		//	//	//bigredbullet = new Bullet(735, 400, "bigredbullet24.bmp");
		//	//	beam1_bool = false;
		//	//}
		//	if (beam1_height <= 0)
		//	{
		//		beam1_height = 0;
		//		beam1_speed = 0;
		//		beam1_hold += 1;
		//		if (beam1_hold == 200)
		//		{
		//			beam1_height = 450;
		//			beam1_hold = 0;
		//			beam1_bool = false;
		//		}
		//	}
		//}

		//if (!beam1_bool)
		//{
		//	if (nextBool(0.05))
		//	{
		//		beam1_speed = 50;
		//		beam1_bool = true;
		//	}
		//}


		//COLLISION CODE
		UpdateCollision();

		
		
		
	}
	else if (!game_over)
	{
		GetCursorPos(&cursor_point);
		ScreenToClient(wnd.hWnd, &cursor_point);
		intro_screen->Change_difficulty(cursor_point.x, cursor_point.y, isStarted);
	}
	

	
	
}



void Game::ComposeFrame()
{
	if (game_over)
	{
		end_screen->Draw_End(gfx);
	}
	else if (isStarted)
	{

		
		//DRAW WIZ
		wizard->Draw(gfx);
		if (wiz_shot_at_bool)
		{
			shot_wiz->Draw(gfx);
		}

		//DRAW ENEMIES AND LEGS
		gunbot->Draw(gfx);
		gunbot_legs->Draw_legs(gfx);

		lazerbot->Draw(gfx);
		lazerbot_legs->Draw_legs(gfx);
		
		//DRAW LIFEBAR
		wiz_life_bar->Draw(gfx);

		//DRAW OBSTICLES
		ballbot->Draw(gfx);


		



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
		

		
		
		


		wiz_life_bar->Draw(gfx);

	}
	else 
	{
		for (int x = 0; x < Graphics::ScreenWidth; x++) {
			for (int y = 0; y < Graphics::ScreenHeight; y++) {
				gfx.PutPixel(x, y, 255, 255, 255);
			}
		}
		intro_screen->Draw_Intro(gfx);

		time_between_frames = clock() - time_between_frames;
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 10, 10, time_between_frames, Color(0, 0, 0));
		time_between_frames = clock();
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 50, 10, ++frame_counter, Color(0, 0, 0));
	}

	
	slug->Draw(gfx);
	
	gunbot->Draw_bullet(gfx);
	lazerbot->Draw_missile(gfx);
	if (slug->death && !slug->exploded)
	{

		explosion_sheet->drawFrame(gfx, explosion_anime->getCurrentFrame(), wizard->GetX(), wizard->GetY());
		explosion_anime->nextFrame();
		if (explosion_anime->getCurrentFrame() >= slug->explode_max_frame_count)
		{
			slug->exploded = true;
		}
	}
	if (paused)
	{
		pause_screen->Draw_Pause(gfx);
	}
}

bool Game::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}



double Game::GetDegree(int a1, int a2, int b1, int b2)
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

void Game::UpdateCollision()
{
	//ALL IF STATEMENTS DOWN HERE ARE COLLISIONS
	int wiz_x = wizard->GetX();
	int wiz_y = wizard->GetY();
	int bullet_x = gunbot->bullet->x;
	int bullet_y = gunbot->bullet->y;
	int lazer1_x = lazer1->x;
	int lazer1_y = lazer1->y;
	int lazer2_x = lazer2->x;
	int lazer2_y = lazer2->y;
	wiz_shot_at_bool = false;

	//wiz and slug
	if ((wizard->GetX() < slug->x + slug->sheet->Width()) && (wizard->GetY() < slug->y + slug->sheet->Height())
		&& ((wizard->GetX() + wiz_sheet->Width() > slug->x) && (wizard->GetY() < slug->y + slug->sheet->Height()))
		&& ((wizard->GetX() < slug->x + slug->sheet->Width()) && (wizard->GetY() + wiz_sheet->Height() > slug->y))
		&& ((wizard->GetX() + wiz_sheet->Width() > slug->x) && (wizard->GetY() + wiz_sheet->Height() > slug->y) && !slug->death)
		)
	{
		wizard->lives -= 10;
		wiz_shot_at_bool = true;
		slug->death = true;
	}

	////wiz and gun_bullet
	if ((wiz_x < bullet_x + gunbot->bullet->sheet->Width()) && (wiz_y < bullet_y + gunbot->bullet->sheet->Height())
		&& ((wiz_x + wiz_sheet->Width() > bullet_x) && (wiz_y < bullet_y + gunbot->bullet->sheet->Height()))
		&& ((wiz_x < bullet_x + gunbot->bullet->sheet->Width()) && (wiz_y + wiz_sheet->Height() > bullet_y))
		&& ((wiz_x + wiz_sheet->Width() > bullet_x) && (wiz_y + wiz_sheet->Height() > bullet_y))
		)
	{
		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	//wiz and left_missile
	if ((wiz_x < lazerbot->left_missile->x + lazerbot->left_missile->sheet->Width()) && (wiz_y < lazerbot->left_missile->y + lazerbot->left_missile->sheet->Height())
		&& ((wiz_x + wiz_sheet->Width() > lazerbot->left_missile->x) && (wiz_y < lazerbot->left_missile->y + lazerbot->left_missile->sheet->Height()))
		&& ((wiz_x < lazerbot->left_missile->x + lazerbot->left_missile->sheet->Width()) && (wiz_y + wiz_sheet->Height() > lazerbot->left_missile->y))
		&& ((wiz_x + wiz_sheet->Width() > lazerbot->left_missile->x) && (wiz_y + wiz_sheet->Height() > lazerbot->left_missile->y))
		)
	{

		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	//wi and lazer 2
	if ((wiz_x < lazerbot->right_missile->x + lazerbot->right_missile->sheet->Width()) && (wiz_y < lazerbot->right_missile->y + lazerbot->right_missile->sheet->Height())
		&& ((wiz_x + wiz_sheet->Width() > lazerbot->right_missile->x) && (wiz_y < lazerbot->right_missile->y + lazerbot->right_missile->sheet->Height()))
		&& ((wiz_x < lazerbot->right_missile->x + lazerbot->right_missile->sheet->Width()) && (wiz_y + wiz_sheet->Height() > lazerbot->right_missile->y))
		&& ((wiz_x + wiz_sheet->Width() > lazerbot->right_missile->x) && (wiz_y + wiz_sheet->Height() > lazerbot->right_missile->y))
		)
	{

		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	////wiz and beam
	//if (((wiz_x < 730 + beam1_width && wiz_x > 730) || (wiz_x + wiz_sheet->Width() > 730 && wiz_x + wiz_sheet->Width() < 730 + beam1_width)
	//	|| (wiz_x + wiz_sheet->Width() / 2 < 730 + beam1_width && wiz_x + wiz_sheet->Width() / 2 > 730))
	//	&& beam1_height < wiz_y)
	//{
	//	wizard->lives -= 1;
	//	wiz_shot_at_bool = true;
	//}
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

	ballbot = new Ballbot(400, 400, 600, 400, 350, 500, "ballRobot24.bmp", 1, 1);


	//bigredbullet = new Bullet(735, 400, "bigredbullet24.bmp");
	//itsover = new Surface("pressenter.bmp");

	beam1_bool = false;

	lazer_bullet1 = false;

	lazer_bullet2 = false;
	
	gunbot = new Turret(LEFT, 600, 300, 1, "gunbot.bmp", "bigredbullet24.bmp",4, 2, 55, 55, 10);
	gunbot_legs = new Enemy(LEFT, 600, 300, 1, "gunbot_legs.bmp", 3, 1, 55, 55, 100);

	lazerbot = new LazerBot(LEFT, 400, 300, 2, "lazerbot.bmp", 2, 2, 0, 0, 10);
	lazerbot_legs = new Enemy(LEFT, 400, 300, 2, "lazerbot_legs.bmp", 2, 1, 0, 0, 10);

	slug = new Slug(LEFT, 500, 200, 1, "slug.bmp", 5, 1, 0, 0, 10);
	slug->chase_vector = new Vector(0, 5);


	//lazer1 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");//left missile
	//lazer2 = new Bullet(lazerbot->x, lazerbot->y, "lazer.bmp");//right missile

	

	game_over = false;

	wiz_shot_at_bool = false;

	intro_screen = new TitleScreen(0, 0, "titlescreen.bmp", 6, 1);
	end_screen = new TitleScreen(0, 0, "end_screen.bmp", 2, 2);
	end_screen_win = new TitleScreen(0, 0, "end_screen_win.bmp", 2, 2);
	pause_screen = new TitleScreen(0, 0, "pause_screen.bmp", 2, 2);

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

	explosion_sheet = new SpriteSheet("explosion.bmp", 2, 2);
	explosion_anime = new Animation(-1, 8, 0, 3);



	//THEM LISTS FOR YOU MAX
	characters.push_back(wizard);
	characters.push_back(shot_wiz);

	enemies.push_back(gunbot);
	enemies.push_back(lazerbot);


	obstacles.push_back(ballbot);
	
}

void Game::Replay()
{
	Restart();
	isStarted = true;
}

void Game::Update_when_paused()
{
	GetCursorPos(&cursor_point);
	ScreenToClient(wnd.hWnd, &cursor_point);
	pause_screen->pause_screen_select(cursor_point.x, cursor_point.y, paused,isRe_started);

}

