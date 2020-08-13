
#include "Game.h"

#pragma comment(lib,"winmm")
#include <iostream>
using namespace std;
template<typename Base, typename T>
inline bool instanceof(const T*) {
	return is_base_of<Base, T>::value;
}

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
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		game_won = true;
	}

	else if (game_won)
	{
		GetCursorPos(&cursor_point);
		ScreenToClient(wnd.hWnd, &cursor_point);
		won_screen->won_screen_select(cursor_point.x, cursor_point.y, *wizard, isRe_started, is_Replay);
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
			if (!enemies[i]->shocked)
			{
				enemies[i]->randomMove(obstacles, 0, 0);
			}
		}
		/*gunbot->clamp_screen(100, 100, 100, 150);
		lazerbot->clamp_screen(150, 150, 150, 150);*/

		//LEGS CODE
		gunbot_legs->x = gunbot->x;
		gunbot_legs->y = gunbot->y;

		lazerbot_legs->x = lazerbot->x;
		lazerbot_legs->y = lazerbot->y;

		//LIFEBAR CODE
		wiz_life_bar->width = round(wizard->lives);
		wiz_life_bar->Update_pos(wizard->GetX(), wizard->GetY());

		gunbot->lifebar->width = round(gunbot->lives);
		gunbot->lifebar->Update_pos(gunbot->x, gunbot->y);

		lazerbot->lifebar->width = round(lazerbot->lives);
		lazerbot->lifebar->Update_pos(lazerbot->x, lazerbot->y);

		//ATTACK CODE
		slug->Move_to_character(*wizard);
		gunbot->Update_bullet(*wizard);
		lazerbot->Update_bullet();
		ballbot->Update_Beams();

		//COLLISION CODE
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->y > 450)
			{
				enemies[i]->shocked = true;
				enemies[i]->death = true;
			}
		}

		//PUT DEAD ENEMIES IN QUEUE
		if (slug->death)
		{
			robot_maker->dead_slugs_gunbots.push(slug);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			
			
		}

		//SYNTHESIZE BOTS.
		if (robot_maker->is_closed && robot_maker->dead_slugs_gunbots.size() > 0)
		{
			robot_maker->dead_slugs_gunbots.front()->death = false;
			robot_maker->dead_slugs_gunbots.pop();
		}

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
	else if (game_won)
	{
		won_screen->Draw_Won(gfx);
	}
	else if (isStarted)
	{

		//DRAW MAP
		factory_sheet->drawFrame(gfx, factory_anime->getCurrentFrame(), 0, 0);
		factory_anime->nextFrame();

		//DRAW WIZ
		wizard->Draw(gfx);
		if (wiz_shot_at_bool)
		{
			shot_wiz->Draw(gfx);
		}

		//DRAW BULLETS
		gunbot->Draw_bullet(gfx);
		lazerbot->Draw_missile(gfx);

		//DRAW ENEMIES AND LEGS
		slug->Draw(gfx);

		
		gunbot->Draw(gfx);
		gunbot_legs->Draw_legs(gfx);
		

		lazerbot->Draw(gfx);
		lazerbot_legs->Draw_legs(gfx);
		
		//DRAW LIFEBAR
		wiz_life_bar->Draw(gfx);
		gunbot->lifebar->Draw(gfx);
		lazerbot->lifebar->Draw(gfx);

		//DRAW OBSTICLES
		ballbot->Draw(gfx);
		ballbot->Draw_beams(gfx);
		//robot_maker->Draw(gfx);


	



		

		time_between_frames = clock() - time_between_frames;
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 10, 10, time_between_frames, Color(0, 0, 0));
		time_between_frames = clock();
		draw.WriteNumber(gfx, Graphics::ScreenWidth - 50, 10, ++frame_counter, Color(0, 0, 0));
		

		
		
		


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

	//wiz and gunbot
	if (Detect_Collision(wiz_x, wiz_y, wiz_x + wiz_sheet->Width(), wiz_y + wiz_sheet->Height(),
		gunbot->bullet->x, gunbot->bullet->y, gunbot->bullet->x + gunbot->bullet->sheet->Width(), gunbot->bullet->y + gunbot->bullet->sheet->Height()
	))
	{
		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	//wiz and middle beam
	if (Detect_Collision(wiz_x, wiz_y, wiz_x + wiz_sheet->Width(), wiz_y + wiz_sheet->Height(),
		ballbot->beam1_x, ballbot->beam1_height, ballbot->beam1_x + ballbot->beam1_width, ballbot->beam1_unchanged_height))
	{
		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	if (Detect_Collision(wiz_x, wiz_y, wiz_x + wiz_sheet->Width(), wiz_y + wiz_sheet->Height(),
		ballbot->left_beam_width, ballbot->left_beam_starting_height, ballbot->left_beam_width_right, ballbot->left_beam_starting_height + ballbot->left_beam_height))
	{
		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}

	if (Detect_Collision(wiz_x, wiz_y, wiz_x + wiz_sheet->Width(), wiz_y + wiz_sheet->Height(),
		ballbot->right_beam_width_left, ballbot->right_beam_starting_height, ballbot->right_beam_width, ballbot->right_beam_starting_height + ballbot->right_beam_height))
	{
		wizard->lives -= 0.1;
		wiz_shot_at_bool = true;
	}
	

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

bool Game::Detect_Collision(int x1, int y1, int x1plus, int y1plus, int x2, int y2, int x2plus, int y2plus)
{
	if (((x1 < x2plus) && (y1 < y2plus))
		&& ((x1plus > x2) && (y1 < y2plus))
		&& ((x1 < x2plus) && (y1plus > y2))
		&& ((x1plus > x2) && (y1plus > y2))
		)
	{
		return true;
		
	}
	return false;
}

//DONT LOOK INSIDE THIS FUNCTION 
void Game::Restart()
{
	paused = false;
	isRe_started = false;
	is_Replay = false;
	isStarted = false;
	game_over = false;
	game_won = false;
	frame_counter = 0;
	time_between_frames = clock(); // makes the first measure inaccurate, fuck it though
								   //window = wnd.hWnd;
	wizard = new Wizard(200, 200, "Wizard.bmp", 4, 3);
	shot_wiz = new Wizard(200, 200, "Wiz_shot.bmp", 4, 3);

	std::uniform_int_distribution<int> vDist(-1, 1);

	rock = new Surface("fatrock24.bmp");
	map1 = new Surface("map1.bmp");

	ballbot = new Ballbot(800, 360, 600, 800, 350, 500, "ballbot.bmp", 1, 1);
	robot_maker = new BotMaker(800, 100, 800, 900, 100, 200, "robot_maker.bmp", 2, 2);
	river = new Obstacle(-1, -1, 0, 1120, 400, 630, "map1.bmp", 1, 1);
	

	beam1_bool = false;

	lazer_bullet1 = false;

	lazer_bullet2 = false;
	
	gunbot = new Turret(LEFT, 600, 300, 1, "gunbot.bmp", "bigredbullet24.bmp",4, 2, 55, 55, 100);
	gunbot_legs = new Enemy(LEFT, 600, 300, 1, "gunbot_legs.bmp", 3, 1, 55, 55, 100);

	lazerbot = new LazerBot(LEFT, 400, 300, 2, "lazerbot.bmp", 2, 2, 0, 0, 100);
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
	won_screen = new TitleScreen(0, 0, "won_end_screen.bmp", 2, 2);

	wiz_life_bar = new LifeBar(wizard->GetX(), wizard->GetY(), wizard->lives, 15);


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

	factory_sheet = new SpriteSheet("Factory.bmp", 5, 1);
	factory_anime = new Animation(-1, 8, 0, 4);

	//THEM LISTS FOR YOU MAX
	characters.push_back(wizard);
	characters.push_back(shot_wiz);

	enemies.push_back(gunbot);
	enemies.push_back(lazerbot);

	botmakers.push_back(robot_maker);
	//obstacles.push_back(ballbot);
	//obstacles.push_back(robot_maker);
	//obstacles.push_back(river);
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

