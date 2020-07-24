#pragma once
#include <stdlib.h>
#include <vector>


class Animation
{
private:
	int cancelable_start_frame;
	int frame_skips;
	std::vector<int> frames;
	int num_frames;

	int cur_frame_skip;
	int current_frame;
public:
	Animation(int cancelable_start_frame, int frame_skips, int num_frames, int *fs);
	Animation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame);
	int getCurrentFrame();
	void nextFrame();
	bool isCancelable();
	void reset();
};

