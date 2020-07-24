#include "Animation.h"

Animation::Animation(int cancelable_start_frame, int frame_skips, int num_frames, int * fs)
{
	this->cancelable_start_frame = cancelable_start_frame;
	this->frame_skips = frame_skips;
	this->num_frames = num_frames;
	frames = {};
	for (int i = 0; i < num_frames; i++)
	{
		frames.push_back(*(fs + i));
	}
	cur_frame_skip = 0;
	current_frame = 0;
}

Animation::Animation(int cancelable_start_frame, int frame_skips, int start_frame, int end_frame)
{
	this->cancelable_start_frame = cancelable_start_frame;
	this->frame_skips = frame_skips;
	this->num_frames = 1 + end_frame - start_frame;
	frames = {};
	for (int i = 0; i < num_frames; i++)
	{
		frames.push_back(start_frame + i);
	}
	cur_frame_skip = 0;
	current_frame = 0;
}
	
void Animation::nextFrame()
{
	if (cur_frame_skip < frame_skips)
	{
		cur_frame_skip++;
	}
	else
	{
		if (current_frame < num_frames - 1)
		{
			current_frame++;
		}
		else
		{
			current_frame = 0;
		}
		cur_frame_skip = 0;
	}
}

int Animation::getCurrentFrame()
{
	return frames.at(current_frame);
}
	
bool Animation::isCancelable()
{
	return (cancelable_start_frame <= current_frame || cancelable_start_frame == -1);
}
	
void Animation::reset()
{
	current_frame = 0;
	cur_frame_skip = 0;
}