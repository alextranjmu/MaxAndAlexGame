
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
		Drawer draw;
		PPM *file = new PPM("C:\\Users\\Anh Alexander Tran\\Documents\\Beginner Tutorial 13 Code\\Beginner Tutorial 13 Code\\Engine\\gunrobot.ppm");
		draw.DrawPPM(gfx, 300, 300, file);
		PPM *file1 = new PPM("default_pose1.ppm");
		draw.DrawPPM(gfx, 500, 300, file1);
		cop->Draw(gfx);
	}
}
