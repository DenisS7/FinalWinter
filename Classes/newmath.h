#pragma once

class newmath
{
public:
	struct ivec2
	{
		int x;
		int y;
	};

	struct spriteData {
		char* path;
		int rows, columns;
		float frameTime;
	};

	struct Rect {
		int x;
		int y;
		int height;
		int width;
	};

	static bool inRange(int n, int min, int max);
	static bool isIncluded(int n, int v[], int vsize);
	static void clamp(int& n, int min, int max);
	static int getIndex(int n, int v[], int vsize);
	static void setRect(Rect& box, int nx, int ny, int nheight, int nwidth);
};

