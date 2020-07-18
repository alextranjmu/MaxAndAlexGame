#include "Character.h"
#include "Graphics.h"

Character::Character()
{
	defaultFrame = new PPM("default_pose.ppm");
	runFrames[0] = new PPM("run_keyframes_1.ppm");
	runFrames[1] = new PPM("run_keyframes_2.ppm");
	runFrames[2] = new PPM("run_keyframes_3.ppm");
	runFrames[3] = new PPM("run_keyframes_4.ppm");
	direction = NO_DIRECTION;
	x = 100;
	y = 100;
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		delete runFrames[i];
	}
	delete defaultFrame;
}

void Character::ClampToScreen()
{
	
	const int right = x;
	if( x < 0 )
	{
		x = 0;
	}
	else if( right > Graphics::ScreenWidth - 100 )
	{
		x = (Graphics::ScreenWidth - 100);
	}

	const int bottom = y;
	if( y < 0 )
	{
		y = 0;
	}
	else if( bottom > Graphics::ScreenHeight-50 )
	{
		y = (Graphics::ScreenHeight-50);
	}
}

void Character::Draw( Graphics& gfx ) const
{
	Drawer draw;
	switch (direction)
	{
	case NO_DIRECTION:
		draw.DrawPPM(gfx, x, y, defaultFrame);
		break;
	case UP:
		draw.DrawPPM(gfx, x, y, runFrames[current_run_frame]); // placeholder
		break;
	case DOWN:
		draw.DrawPPM(gfx, x, y, runFrames[current_run_frame]); // placeholder
		break;
	case LEFT:
		draw.DrawPPM_Horizontal_Flip(gfx, x, y, runFrames[current_run_frame]);
		break;
	case RIGHT:
		draw.DrawPPM(gfx, x, y, runFrames[current_run_frame]);
		break;
	}
}

void Character::Update( const Keyboard & kbd, int x1, int x2, int y1, int y2)
{
	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		x += SPEED;
		if (direction == RIGHT)
		{
			collisionUpdatexdown(x1, x2, y1, y2);
			nextRunFrame();

		}
		else
		{
			direction = RIGHT;
			current_run_frame = 0;
		}
	}
	if( kbd.KeyIsPressed( VK_LEFT ) )
	{
		x -= SPEED;
		if (direction == LEFT)
		{
			collisionUpdatexup(x1, x2, y1, y2);
			nextRunFrame();
		}
		else
		{
			direction = LEFT;
			current_run_frame = 0;
		}
	}
	if( kbd.KeyIsPressed( VK_DOWN ) )
	{

		y += SPEED;
		collisionUpdateydown(x1, x2, y1, y2);

	}
	if( kbd.KeyIsPressed( VK_UP ) )
	{
		y -= SPEED;
		collisionUpdateyup(x1, x2, y1, y2);

	}
	if (kbd.KeyIsPressed(VK_SPACE)) {
		
	}
}

int Character::GetX() const
{
	return x;
}

int Character::GetY() const
{
	return y;
}

int Character::GetWidth() const
{
	return width;
}

int Character::GetHeight() const
{
	return height;
}


// Helper functions
void Character::nextRunFrame()
{
	if (current_run_frame == RUN_FRAME_COUNT - 1)
	{
		current_run_frame = 0;
	}
	else
	{
		current_run_frame++;
	}
}

void Character::collisionUpdatexup(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x += SPEED;
	}
}

void Character::collisionUpdatexdown(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		x -= SPEED;
	}
}


void Character::collisionUpdateyup(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y += SPEED;
	}
}

void Character::collisionUpdateydown(int x1, int x2, int y1, int y2)
{
	if ((x) > x1 && (x) < x2 && (y) > y1 && (y) < y2)
	{
		y -= SPEED;
	}
}
