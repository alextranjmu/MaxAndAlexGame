
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <windows.h>
#include "Block.h"
#include "Graphics.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	xDist( 0,770 ),
	yDist( 0,570 )
	
{
	
	ballBot = new Obstacle(500, 300);
	cop = new Character();
	std::uniform_int_distribution<int> vDist(-1, 1);
	
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

	isStarted = true;
	if( isStarted )
	{
		cop->Update(wnd.kbd);
		cop->ClampToScreen();
	}
	else
	{

		if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
		{
			isStarted = true;
		}
	}
}

void Game::DrawGameOver(int x, int y) 
{

}

void Game::DrawTitleScreen(int x, int y) 
{

}

void Game::ComposeFrame()
{
	if( !isStarted )
	{
	}
	else
	{
		/*
		gfx.PutPixel(100, 100, 102, 154, 153);
		Drawer::DrawRectangle(gfx, 100, 100, 100 ,
			150, 102, 154, 153);

		Drawer::DrawRectangle(gfx, 300, 300, 100,
			150, 102, 154, 153);

		Drawer::DrawRectangle(gfx, 700, 300, 100,
			300, 102, 154, 153);

		Drawer::DrawRectangle(gfx, 900, 150, 100,
			200, 102, 154, 153);
			*/
		for (int x = 0; x < Graphics::ScreenWidth; x++)
		{
			for (int y = 0; y < Graphics::ScreenHeight; y++)
			{
				gfx.PutPixel(x, y, 102, 154, 153);
			}
		}
		Drawer draw;
		//PPM *file = new PPM("ballRobot.ppm");
		//draw.DrawPPM(gfx, 0, 0, file);
		ballBot->Draw(gfx);
		cop->Draw(gfx);
	}
}
