
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

	wizard = new Wizard(100, 100, "Wizard.bmp", 4, 3);
	std::uniform_int_distribution<int> vDist(-1, 1);
	rock = new Surface("fatrock24.bmp");
	map1 = new Surface("map1.bmp");
	pressenter = new Surface("pressenter.bmp");
	ballBot = new Surface("ballRobot24.bmp");
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

	beam1_width = 47;
	beam1_height = 0;
	beam1_hold = 0;
	beam1_speed = 30;
	 
	wiz_sheet = new SpriteSheet("Wizard.bmp", 4, 3);
	wiz_anime = new Animation(-1, 3, 6, 11);

	beach_sheet = new SpriteSheet("beach.bmp", 5, 1);
	beach_anime = new Animation(-1, 8, 0, 4);

	tree_sheet = new SpriteSheet("palmtree.bmp", 2, 2);
	tree_anime = new Animation(-1, 8, 0, 3);

	rock_sheet = new SpriteSheet("rock.bmp", 1, 1);
	rock_anime = new Animation(-1, 0, 0, 0);

	flipped_palm_tree_sheet = new SpriteSheet("flipped_palm_tree.bmp", 2, 2);
	flipped_palm_tree_anime = new Animation(-1, 8, 0, 3);


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
		wizard->Update(wnd.kbd, 600, 800, 300, 550);
		wizard->ClampToScreen(wiz_sheet->Width(), wiz_sheet->Height());
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
		//bigredbullet->Accelerate(2, 10);
		//if (bigredbullet->y == 0)
		//{
		//	bigredbullet->x = 735;
		//	bigredbullet->y = 400;
		//	//bigredbullet = new Bullet(735, 400, "bigredbullet24.bmp");
		//	beam1_bool = false;
		//}
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
			lazer1->x = lazerbot->x - lazer1->s->getWidth();
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

	

	
	
	UpdateLazer1();


	gunbot->randomMove();
	gunbot->clamp_screen();


	lazerbot->randomMove();
	lazerbot->clamp_screen_lazer();
	
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

		

		gfx.drawSurface(600, 350, *ballBot);


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

	/*wiz_sheet->drawFrame(gfx, wiz_anime->getCurrentFrame(), 100, 100);
	wiz_anime->nextFrame();*/


}

bool Game::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}

void Game::UpdateLazer1()
{
	int copx = wizard->GetX() + 100;
	int copy1 = wizard->GetY();
	int copy2 = wizard->GetY() + 100;
	if ( copx > lazer1->x && ((copy1 < lazer1->y && copy2 > lazer1->y) || (copy1 < (lazer1->y + lazer1->s->getHeight()) 
		&& copy2 >(lazer1->y + lazer1->s->getHeight()))))
	{
		game_over = true;
	}
}

void Game::UpdateLazer2()
{
	int copx = wizard->GetX();
	int copy1 = wizard->GetY();
	int copy2 = wizard->GetY() + 100;
	if (copx < (lazer2->x + lazer2->s->getWidth()) && ((copy1 < lazer2->y && copy2 > lazer2->y) || (copy1 < (lazer2->y + lazer2->s->getHeight()) && copy2 >(lazer2->y + lazer2->s->getHeight()))))
	{
		game_over = true;
	}
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
