#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "PPM.h"
#include "Drawer.h"

class Obstacle {
public:
	Obstacle(int xPos, int yPos);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd);

private:
	static int const RUN_FRAME_COUNT = 2;
	int current_frame;
	int state;
	int x;
	int y;
	static constexpr int width = 100;
	static constexpr int height = 100;
	PPM *runFrames[RUN_FRAME_COUNT];
	PPM *defaultFrame;
	void nextRunFrame();



};