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
	
	const int right = x + width;
	if( x < 0 )
	{
		x = 0;
	}
	else if( right >= Graphics::ScreenWidth )
	{
		x = (Graphics::ScreenWidth - 1) - width;
	}

	const int bottom = y + height;
	if( y < 0 )
	{
		y = 0;
	}
	else if( bottom >= Graphics::ScreenHeight )
	{
		y = (Graphics::ScreenHeight - 1) - height;
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

void Character::Update( const Keyboard & kbd )
{
	direction = NO_DIRECTION;
	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		x += SPEED;
		if (direction == RIGHT)
		{
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
	}
	if( kbd.KeyIsPressed( VK_UP ) )
	{
		y -= SPEED;
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
