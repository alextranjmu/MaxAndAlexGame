#include "Ballbot.h"
#include "Graphics.h"
Ballbot::Ballbot(int x, int y, int x1, int x2, int y1, int y2, std::string fileName, int rows, int columns)
	: Obstacle(x, y, x1, x2, y1, y2, fileName, rows, columns)
{

}

void Ballbot::Update_Beams()
{
	if (beam1_bool)
	{
		beam1_height -= beam1_speed;
	
		if (beam1_height <= 0)
		{
			beam1_height = 0;
			beam1_speed = 0;
			beam1_hold += 1;
			if (beam1_hold == 200)
			{
				beam1_height = this->x + 130;
				beam1_hold = 0;
				beam1_bool = false;
			}
		}

	}

	if (!beam1_bool)
	{
		if (nextBool(0.005))
		{
			beam1_speed = 15;
			beam1_bool = true;
			
		}
	}

	if (left_beam_bool)
	{
		left_beam_width -= left_beam_speed;
			if (left_beam_width <= 0)
			{
				left_beam_width = 0;
				left_beam_speed = 0;
				left_beam_hold += 1;
				if (left_beam_hold == 200)
				{
					left_beam_width = this->x + 90;
					left_beam_hold = 0;
					left_beam_bool = false;
				}
			}
		
	}

	if (!left_beam_bool)
	{
		if (nextBool(0.005))
		{
			//left_beam_width = 600;
			left_beam_speed = 15;
			left_beam_bool = true;
		}
	}

	if (right_beam_bool)
	{
		right_beam_width += right_beam_speed;
		if (right_beam_width > Graphics::ScreenWidth - 1)
		{
			right_beam_width = Graphics::ScreenWidth;
			right_beam_speed = 0;
			right_beam_hold += 1;
			if (right_beam_hold == 200)
			{
				right_beam_width = this->x + 210;
				right_beam_hold = 0;
				right_beam_bool = false;
			}

		}
	}

	if (!right_beam_bool)
	{
		if (nextBool(0.005))
		{
			right_beam_speed = 15;
			right_beam_bool = true;
		}
	}

}

void Ballbot::Draw_beams(Graphics &gfx)
{
	if (beam1_bool)
	{
		int x = this->x + 130;
		for (; x < beam1_width + this->x + 130; x++)
		{
			for (int y = this->y + 100; y > beam1_height; y--)
			{
				gfx.PutPixel(x, y, 222, 34, 34);
			}
		}

	}

	if (left_beam_bool)
	{
		for (int x = this->x + 90; x > left_beam_width; x--)
		{
			for (int y = this->y + 80; y < left_beam_height + this->y + 80; y++)
			{
				gfx.PutPixel(x, y, 224, 34, 34);
			}
		}
	}

	if (right_beam_bool)
	{
		for (int x = this->x + 210; x < right_beam_width; x++)
		{
			for (int y = this->y + 80; y < right_beam_height + this->y + 80; y++)
			{
				gfx.PutPixel(x, y, 224, 34, 34);
			}
		}
	}
}


//void Ballbot::Update_Beams()
//{
//	if (beam1_bool)
//	{
//		beam1_height -= beam1_speed;
//
//		if (beam1_height <= 0)
//		{
//			beam1_height = 0;
//			beam1_speed = 0;
//			beam1_hold += 1;
//			if (beam1_hold == 200)
//			{
//				beam1_height = 450;
//				beam1_hold = 0;
//				beam1_bool = false;
//			}
//		}
//
//	}
//
//	if (!beam1_bool)
//	{
//		if (nextBool(0.005))
//		{
//			beam1_speed = 15;
//			beam1_bool = true;
//
//		}
//	}
//
//	if (left_beam_bool)
//	{
//		left_beam_width -= left_beam_speed;
//		if (left_beam_width <= 0)
//		{
//			left_beam_width = 0;
//			left_beam_speed = 0;
//			left_beam_hold += 1;
//			if (left_beam_hold == 200)
//			{
//				left_beam_width = 690;
//				left_beam_hold = 0;
//				left_beam_bool = false;
//			}
//		}
//
//	}
//
//	if (!left_beam_bool)
//	{
//		if (nextBool(0.005))
//		{
//			//left_beam_width = 600;
//			left_beam_speed = 15;
//			left_beam_bool = true;
//		}
//	}
//
//	if (right_beam_bool)
//	{
//		right_beam_width += right_beam_speed;
//		if (right_beam_width > Graphics::ScreenWidth - 1)
//		{
//			right_beam_width = Graphics::ScreenWidth;
//			right_beam_speed = 0;
//			right_beam_hold += 1;
//			if (right_beam_hold == 200)
//			{
//				right_beam_width = 810;
//				right_beam_hold = 0;
//				right_beam_bool = false;
//			}
//
//		}
//	}
//
//	if (!right_beam_bool)
//	{
//		if (nextBool(0.005))
//		{
//			right_beam_speed = 15;
//			right_beam_bool = true;
//		}
//	}
//
//}
//
//void Ballbot::Draw_beams(Graphics &gfx)
//{
//	if (beam1_bool)
//	{
//		int x = 730;
//		for (; x < beam1_width + 730; x++)
//		{
//			for (int y = 450; y > beam1_height; y--)
//			{
//				gfx.PutPixel(x, y, 222, 34, 34);
//			}
//		}
//
//	}
//
//	if (left_beam_bool)
//	{
//		for (int x = 690; x > left_beam_width; x--)
//		{
//			for (int y = 430; y < left_beam_height + 430; y++)
//			{
//				gfx.PutPixel(x, y, 224, 34, 34);
//			}
//		}
//	}
//
//	if (right_beam_bool)
//	{
//		for (int x = 810; x < right_beam_width; x++)
//		{
//			for (int y = 430; y < right_beam_height + 430; y++)
//			{
//				gfx.PutPixel(x, y, 224, 34, 34);
//			}
//		}
//	}
//}
