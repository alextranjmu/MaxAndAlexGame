
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <windows.h>


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng( rd() ),
	
	xDist( 0,770 ),
	yDist( 0,570 ) 
	
{
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
		dude.Update( wnd.kbd );
		dude.ClampToScreen();

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
		draw.DrawRectangle(gfx, 0, 0, 200, 100, 239, 245, 66);

		
		dude.Draw( gfx );

		
	}
}
