#include "PPM.h"

using namespace std;

PPM::PPM()
{
}

PPM::PPM(char* fileName)
{
	char magic[10];
	char w[10];
	char h[10];
	char mc[10];
	FILE *ppm = fopen("default_pose.ppm", "r");
	if (ppm != NULL)
	{
		int count = fscanf(ppm, "%10[^ \n] %10[^ \n] %10[^ \n] %10[^ \n]", magic, w, h, mc);
		if (count == 4)
		{
			if (strcmp("p6", "p6") == 0 && strcmp("255", "255") == 0) // SHOULD BE magic AND mc RESPECTIVELY
			{
				width = atoi(w); // UNSAFE
				height = atoi(h); // UNSAFE
				freopen(fileName, "rb", ppm);
				pixels = (Pixel*)malloc(height * width * sizeof(Pixel));
				char buffer[3];
				char temp_buffer[20];
				fscanf(ppm, "%20[^\n]", temp_buffer);
				fread(buffer, 1, 1, ppm);
				for (int row = 0; row < height; row++)
				{
					for (int col = 0; col < width; col++)
					{
						if (fread(buffer, 1, 3, ppm) != 3)
						{
							cerr << "file read error?\n";
						}
						else
						{
							//Pixel p = Pixel(buffer[0], buffer[1], buffer[2]); // POTENTIAL CONVERSION ERROR char -> int
							*(pixels + row*width + col) = Pixel(buffer[0], buffer[1], buffer[2]);
						}
					}
				}
			}
			else
			{
				if (strcmp(magic, "p3") != 0)
					cerr << "magic number not right\n";
				if (strcmp(mc, "255") != 0)
					cerr << "max color not right\n";
			}
		}
		else
		{
			cerr << "failed to read text piece of ppm file\n";
		}
		fclose(ppm);
	}
	else
	{
		cerr << fileName << ": null file oh no\n";
	}
}

PPM::~PPM()
{
	free(pixels);
	pixels = nullptr;
}