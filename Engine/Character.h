#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "PPM.h"
#include "Drawer.h"

class Character
{
public:
	Character();
	~Character();
	void ClampToScreen();
	void Draw( Graphics& gfx ) const;
	void Update( const Keyboard& kbd );
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	static int const RUN_FRAME_COUNT = 4;

	static int const NO_DIRECTION = 0;
	static int const UP = 1; // should move these constants to a new file, maybe
	static int const DOWN = 2;
	static int const LEFT = 3;
	static int const RIGHT = 4;

	static const int SPEED = 4;

	int current_run_frame;
	int x;
	int y;
	int direction;
	static constexpr int width = 20;
	static constexpr int height = 20;
	PPM *runFrames[RUN_FRAME_COUNT];
	PPM *defaultFrame;


	//Helper functions
	void nextRunFrame();
};