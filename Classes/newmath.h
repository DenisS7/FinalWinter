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

		friend Rect operator+(const Rect& a, const Rect& b) { return{ a.x + b.x, a.y + b.y, a.height + b.height, a.width + b.width }; }
	};

	static bool inRange(int n, int min, int max);
	static bool isIncluded(int n, int v[], int vsize);
	static int clamp(int n, int min, int max);
	static int getIndex(int n, int v[], int vsize);
	static Rect make_Rect(int nx, int ny, int nheight, int nwidth) 
	{
		Rect newRect;

		newRect.x = nx;
		newRect.y = ny;
		newRect.height = nheight;
		newRect.width = nwidth;
		
		return newRect;
	}
	static ivec2 make_ivec2(int x, int y) { ivec2 a; a.x = x, a.y = y; return a; };
	static int getSign(int n) { if (n < 0) return -1; if (n > 0) return 1; return 0; };
	static bool isNegative(int n) { if (n < 0) return true; return false; };
};

