#pragma once
#include <stdlib.h>


class Animation
{
private:
	int cancelable_start_frame;
	int frame_skips;
	int *frames;
	int num_frames;

	int cur_frame_skip;
	int current_frame;
public:
	~Animation();
	Animation(int cancelable_start_frame, int frame_skips, int num_frames, int *frames);
	Animation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame);
	int getCurrentFrame();
	void nextFrame();
	bool isCancelable();
	void reset();




	int* getFrames();
};

