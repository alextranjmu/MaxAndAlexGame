
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
	rock = new Surface("fatrock24.bmp");
	map1 = new Surface("map1.bmp");
	ballBot = new Surface("ballRobot24.bmp");
	pressenter = new Surface("pressenter.bmp");
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

	if( isStarted )
	{
		cop->Update(wnd.kbd);
		cop->ClampToScreen();
	}
	else
	{

		if( wnd.kbd.KeyIsPressed( VK_RETURN) )
		{
			isStarted = true;
		}
	}
}

void Game::DrawGameOver(int x, int y) 
{

}



void Game::ComposeFrame()
{
	if( isStarted )
	{
		/*for (int x = 0; x < Graphics::ScreenWidth; x++) {
			for (int y = 0; y < Graphics::ScreenHeight; y++) {
				gfx.PutPixel(x, y, 255, 255, 255);
			}
		}*/
		//Surface *map1 = new Surface("map1.bmp");
		gfx.drawSurface(0, 0, *map1);
		cop->Draw(gfx);
		//Surface *rock = new Surface("fatrock24.bmp");
		gfx.drawSurface(200, 200, *rock);
		gfx.drawSurface(900, 300, *rock);
		gfx.drawSurface(600, 50, *rock);

		gfx.drawSurface(500, 300, *ballBot);
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
	}
}
