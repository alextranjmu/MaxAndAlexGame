#include "SpriteSheet.h"



SpriteSheet::SpriteSheet(std::string fileName, int rows, int columns)
{
	Surface *sheet = new Surface(fileName);
	num_frames = rows * columns;
	frame_width = sheet->getWidth() / columns;
	frame_height = sheet->getHeight() / rows;

	frames = (Pixel*)malloc(sizeof(Pixel) * frame_width * frame_height * num_frames);
	int i = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			for (int y = frame_height * (rows-r-1); y < frame_height * (rows-r); y++)
			{
				for (int x = frame_width * c; x < frame_width * (c+1); x++)
				{
					Pixel p = sheet->getPixel(x, y);
					*(frames + (i * frame_width * frame_height) + (y - frame_height * (rows - r - 1)) * frame_width + (x - frame_width * c)) = p;
				}
			}
			i++;
		}
	}
	delete sheet;
}


SpriteSheet::~SpriteSheet()
{
	free(frames);
	frames = nullptr;
}

void SpriteSheet::drawFrame(Graphics & gfx, int frame_num, int x, int y)
{
	for (int row = 0; row < frame_height; row++)
	{
		for (int col = 0; col < frame_width; col++)
		{
			Pixel p = *(frames + (frame_num * frame_height * frame_width) + (row * frame_width) + col);
			if (p.red == -1 && p.blue == -1 && p.green == -1)
			{
				// n word
			}
			else
			{
				if (x + col < Graphics::ScreenWidth && y - row + frame_height < Graphics::ScreenHeight)
				gfx.PutPixel(x + col, y - row + frame_height, p.red, p.green, p.blue);
			}
		}
	}
}

void SpriteSheet::drawFrameHorizontalFlip(Graphics & gfx, int frame_num, int x, int y)
{
	for (int row = 0; row < frame_height; row++)
	{
		for (int col = 0; col < frame_width; col++)
		{
			Pixel p = *(frames + (frame_num * frame_height * frame_width) + (row * frame_width) + col);
			if (p.red == -1 && p.blue == -1 && p.green == -1)
			{
				// n word
			}
			else
			{
				gfx.PutPixel(x - col + frame_width, y - row + frame_height, p.red, p.green, p.blue);
			}
		}
	}
}

int SpriteSheet::Width()
{
	return frame_width;
}

int SpriteSheet::Height()
{
	return frame_height;
}
